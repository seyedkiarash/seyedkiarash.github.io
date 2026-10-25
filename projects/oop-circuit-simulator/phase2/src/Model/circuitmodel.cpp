// =======================================================================
// FILE: circuitmodel.cpp
// =======================================================================
#include "circuitmodel.h"
#include <fstream>
#include <cmath>
#include "Eigen/Dense"
#include "analysis_engine.h"

CircuitModel::CircuitModel() {}

Project& CircuitModel::getProjectData() {
    return project;
}

bool CircuitModel::runAnalysis(const SimulationSettings& settings, const std::string& outputFilePath) {
    std::ofstream outFile(outputFilePath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open output file: " << outputFilePath << std::endl;
        return false;
    }

    project.settings = settings;
    project.lastAnalysisResultPath = outputFilePath;

    switch (settings.type) {
        case SimulationSettings::Transient:
            return runTransientAnalysis(settings, outFile);
        case SimulationSettings::AC:
            return runAcAnalysis(settings, outFile);
        case SimulationSettings::Phase:
            return runPhaseAnalysis(settings, outFile);
    }
    return false;
}

void CircuitModel::buildAnalysisEngine(AnalysisEngine& engine) const {
    // Clear previous data
    engine.nodes.clear();
    engine.nodeNameToIndex.clear();
    engine.resistors.clear();
    engine.capacitors.clear();
    engine.inductors.clear();
    engine.voltageSources.clear();
    engine.currentSources.clear();
    
    // First, ensure ground node exists
    engine.ensureNode("0", true);
    
    // Then add all other nodes
    for (const auto& n : project.nodes) {
        if (!n) continue;
        if (n->getName() != "0" && n->getName() != "GND") {
            engine.ensureNode(n->getName(), false);
        }
    }

    // Now add elements with proper node mapping
    for (const auto& e : project.elements) {
        if (!e) continue;
        
        // Get node names and ensure they exist
        std::string node1Name = e->node1 ? e->node1->getName() : "0";
        std::string node2Name = e->node2 ? e->node2->getName() : "0";
        

        
        // Ensure nodes exist in engine
        int n1 = engine.ensureNode(node1Name, node1Name == "0" || node1Name == "GND");
        int n2 = engine.ensureNode(node2Name, node2Name == "0" || node2Name == "GND");
        
        const std::string t = e->getType();
        
        try {
            if (t == "Resistor") {
                auto r = dynamic_cast<const Resistor*>(e.get());
                if (r) {
                    engine.resistors.push_back({n1, n2, std::max(1e-12, r->resistance)});
                }
            } else if (t == "Capacitor") {
                auto c = dynamic_cast<const Capacitor*>(e.get());
                if (c) {
                    engine.capacitors.push_back({n1, n2, std::max(0.0, c->capacitance)});
                }
            } else if (t == "Inductor") {
                auto L = dynamic_cast<const Inductor*>(e.get());
                if (L) {
                    engine.inductors.push_back({n1, n2, std::max(0.0, L->inductance), -1});
                }
            } else if (t == "VoltageSource" || t == "VoltageSourceDC") {
                auto vs = dynamic_cast<const VoltageSource*>(e.get());
                if (vs) {
                    AnalysisEngine::VS vs_elem;
                    vs_elem.n1 = n1;
                    vs_elem.n2 = n2;
                    vs_elem.type = AnalysisEngine::VS::DC;
                    vs_elem.dc = vs->voltage;
                    engine.voltageSources.push_back(vs_elem);
                }
            } else if (t == "VoltageSourceSin") {
                auto s = dynamic_cast<const VoltageSourceSin*>(e.get());
                if (s) {
                    AnalysisEngine::VS vs_elem;
                    vs_elem.n1 = n1;
                    vs_elem.n2 = n2;
                    vs_elem.type = AnalysisEngine::VS::SIN;
                    vs_elem.dc = 0;
                    vs_elem.amp = s->amplitude;
                    vs_elem.freq = s->frequency;
                    engine.voltageSources.push_back(vs_elem);

                }
            } else if (t == "VoltageSourcePulse") {
                AnalysisEngine::VS vs_elem;
                vs_elem.n1 = n1;
                vs_elem.n2 = n2;
                vs_elem.type = AnalysisEngine::VS::PULSE;
                vs_elem.dc = 0;
                engine.voltageSources.push_back(vs_elem);
                
            } else if (t == "CurrentSource" || t == "CurrentSourceDC") {
                auto cs = dynamic_cast<const CurrentSource*>(e.get());
                if (cs) {
                    AnalysisEngine::IS is_elem;
                    is_elem.n1 = n1;
                    is_elem.n2 = n2;
                    is_elem.type = AnalysisEngine::IS::DC;
                    is_elem.dc = cs->current;
                    engine.currentSources.push_back(is_elem);
                }
            } else if (t == "CurrentSourceSin") {
                auto s = dynamic_cast<const CurrentSourceSin*>(e.get());
                if (s) {
                    AnalysisEngine::IS is_elem;
                    is_elem.n1 = n1;
                    is_elem.n2 = n2;
                    is_elem.type = AnalysisEngine::IS::SIN;
                    is_elem.dc = 0;
                    is_elem.amp = s->amplitude;
                    is_elem.freq = s->frequency;
                    engine.currentSources.push_back(is_elem);

                }
            } else if (t == "CurrentSourcePulse") {
                AnalysisEngine::IS is_elem;
                is_elem.n1 = n1;
                is_elem.n2 = n2;
                is_elem.type = AnalysisEngine::IS::PULSE;
                is_elem.dc = 0;
                engine.currentSources.push_back(is_elem);
                
            } else if (t == "Diode") {
                // Diode not implemented in analysis engine yet
            } else if (t == "ZenerDiode") {
                // Zener diode not implemented in analysis engine yet
            } else if (t == "Ground") {
                // Ground is just a node, already handled
            } else {
                // Unknown element type
            }
        } catch (const std::exception& ex) {
            std::cerr << "Error processing element " << e->name << " of type " << t << ": " << ex.what() << std::endl;
        }
    }
    

}

bool CircuitModel::runTransientAnalysis(const SimulationSettings& settings, std::ofstream& outFile) {
    try {
        AnalysisEngine eng;
        buildAnalysisEngine(eng);
        
        // Check if engine has any elements
        if (eng.resistors.empty() && eng.capacitors.empty() && eng.inductors.empty() && 
            eng.voltageSources.empty() && eng.currentSources.empty()) {
            std::cerr << "Warning: No elements found in circuit for analysis" << std::endl;
            return false;
        }
        
        // Prepare output headers: Time and all non-ground node voltages
        std::vector<std::string> headers;
        headers.push_back("Time");
        
        for (const auto& n : project.nodes) {
            if (n && n->getName() != "GND" && n->getName() != "0") {
                headers.push_back("V(" + n->getName() + ")");
            }
        }
        
        if (headers.size() <= 1) {
            std::cerr << "Warning: No non-ground nodes found for analysis" << std::endl;
            return false;
        }
        
        std::vector<std::vector<double>> data;
        std::vector<std::string> nodeNames;
        for (size_t i = 1; i < headers.size(); ++i) {
            nodeNames.push_back(headers[i].substr(2, headers[i].size() - 3));
        }
        
        // Run transient analysis with error checking
        try {
            eng.runTransient(project.settings.t_start, project.settings.t_stop, project.settings.t_step, nodeNames, data);
        } catch (const std::exception& ex) {
            std::cerr << "Error in transient analysis: " << ex.what() << std::endl;
            return false;
        }
        
        // Validate data
        if (data.empty() || data[0].empty()) {
            std::cerr << "Warning: No data generated from analysis" << std::endl;
            return false;
        }
        
        // Write to file
        for (size_t i = 0; i < headers.size(); ++i) {
            outFile << headers[i];
            if (i + 1 < headers.size()) outFile << "\t";
        }
        outFile << "\n";
        
        size_t rows = data[0].size();
        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < data.size(); ++c) {
                if (c < data.size() && r < data[c].size()) {
                    outFile << data[c][r];
                } else {
                    outFile << "0.0"; // Default value if data is missing
                }
                if (c + 1 < data.size()) outFile << "\t";
            }
            outFile << "\n";
        }
        
        return true;
        
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error in transient analysis: " << ex.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Unknown error in transient analysis" << std::endl;
        return false;
    }
}

bool CircuitModel::runAcAnalysis(const SimulationSettings& settings, std::ofstream& outFile) {
    try {
        AnalysisEngine eng;
        buildAnalysisEngine(eng);
        
        // Check if engine has any elements
        if (eng.resistors.empty() && eng.capacitors.empty() && eng.inductors.empty() && 
            eng.voltageSources.empty() && eng.currentSources.empty()) {
            std::cerr << "Warning: No elements found in circuit for AC analysis" << std::endl;
            return false;
        }
        
        std::vector<std::string> headers;
        std::vector<std::vector<double>> data;
        
        try {
            eng.runAC(project.settings.f_start, project.settings.f_stop, project.settings.points, headers, data);
        } catch (const std::exception& ex) {
            std::cerr << "Error in AC analysis: " << ex.what() << std::endl;
            return false;
        }
        
        // Validate data
        if (data.empty() || data[0].empty()) {
            std::cerr << "Warning: No data generated from AC analysis" << std::endl;
            return false;
        }
        
        // Write headers
        for (size_t i = 0; i < headers.size(); ++i) {
            outFile << headers[i];
            if (i + 1 < headers.size()) outFile << "\t";
        }
        outFile << "\n";
        
        // Write data
        size_t rows = data[0].size();
        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < data.size(); ++c) {
                if (c < data.size() && r < data[c].size()) {
                    outFile << data[c][r];
                } else {
                    outFile << "0.0";
                }
                if (c + 1 < data.size()) outFile << "\t";
            }
            outFile << "\n";
        }
        
        return true;
        
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error in AC analysis: " << ex.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Unknown error in AC analysis" << std::endl;
        return false;
    }
}

bool CircuitModel::runPhaseAnalysis(const SimulationSettings& settings, std::ofstream& outFile) {
    try {
        AnalysisEngine eng;
        buildAnalysisEngine(eng);
        
        // Check if engine has any elements
        if (eng.resistors.empty() && eng.capacitors.empty() && eng.inductors.empty() && 
            eng.voltageSources.empty() && eng.currentSources.empty()) {
            std::cerr << "Warning: No elements found in circuit for phase analysis" << std::endl;
            return false;
        }
        
        std::vector<std::string> headers;
        std::vector<std::vector<double>> data;
        
        try {
            eng.runPhase(project.settings.base_freq, project.settings.p_start, project.settings.p_stop, project.settings.points_phase, headers, data);
        } catch (const std::exception& ex) {
            std::cerr << "Error in phase analysis: " << ex.what() << std::endl;
            return false;
        }
        
        // Validate data
        if (data.empty() || data[0].empty()) {
            std::cerr << "Warning: No data generated from phase analysis" << std::endl;
            return false;
        }
        
        // Write headers
        for (size_t i = 0; i < headers.size(); ++i) {
            outFile << headers[i];
            if (i + 1 < headers.size()) outFile << "\t";
        }
        outFile << "\n";
        
        // Write data
        size_t rows = data[0].size();
        for (size_t r = 0; r < rows; ++r) {
            for (size_t c = 0; c < data.size(); ++c) {
                if (c < data.size() && r < data[c].size()) {
                    outFile << data[c][r];
                } else {
                    outFile << "0.0";
                }
                if (c + 1 < data.size()) outFile << "\t";
            }
            outFile << "\n";
        }
        
        return true;
        
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error in phase analysis: " << ex.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Unknown error in phase analysis" << std::endl;
        return false;
    }
}
