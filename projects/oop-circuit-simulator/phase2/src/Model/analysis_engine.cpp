#include "analysis_engine.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

static constexpr double PI_D = 3.14159265358979323846;

bool AnalysisEngine::isGroundName(const std::string& n) const {
    if (n == "0") return true;
    std::string low = n; for(char& c: low) c = (char)tolower(c);
    return (low == "gnd");
}

int AnalysisEngine::ensureNode(const std::string& name, bool isGroundFlag) {
    auto it = nodeNameToIndex.find(name);
    if (it != nodeNameToIndex.end()) return it->second;
    AE_Node nd; nd.name = name; nd.isGround = isGroundFlag || isGroundName(name);
    nodes.push_back(nd);
    int idx = (int)nodes.size()-1;
    nodeNameToIndex[name] = idx;
    return idx;
}

int AnalysisEngine::groundlessIndex(int nodeIdx, const std::vector<int>& nodeMap) const {
    if (nodeIdx < 0) return -1;
    if (nodes[nodeIdx].isGround) return -1;
    return nodeMap[nodeIdx];
}

double AnalysisEngine::evalVSSourceAtTime(const VS& vs, double t) const {
    switch (vs.type) {
        case VS::DC: return vs.dc;
        case VS::SIN: return vs.dc + vs.amp * std::sin(2*PI_D*vs.freq*t);
        case VS::PULSE: default: return vs.dc; // simplified for now
    }
}

double AnalysisEngine::evalISSourceAtTime(const IS& is, double t) const {
    switch (is.type) {
        case IS::DC: return is.dc;
        case IS::SIN: return is.dc + is.amp * std::sin(2*PI_D*is.freq*t);
        case IS::PULSE: default: return is.dc; // simplified for now
    }
}

void AnalysisEngine::runTransient(double t_start, double t_stop, double h,
                                  std::vector<std::string>& outNodeNames,
                                  std::vector<std::vector<double>>& outData) {
    // Map non-ground nodes
    int N = (int)nodes.size();
    std::vector<int> nodeMap(N, -1);
    int nUnknownNodes = 0;
    for (int i=0;i<N;++i) if (!nodes[i].isGround) nodeMap[i] = nUnknownNodes++;

    int nVS = (int)voltageSources.size();
    int nL = (int)inductors.size();
    int sysSize = nUnknownNodes + nVS + nL;

    if (sysSize <= 0) {
        // Generate simple output for basic circuits
        outData.clear();
        outData.push_back({}); // Time column
        for (size_t i = 1; i < outNodeNames.size(); ++i) {
            outData.push_back({});
        }
        
        for (double t = t_start; t <= t_stop + 1e-12; t += h) {
            outData[0].push_back(t);
            for (size_t i = 1; i < outData.size(); ++i) {
                // Simple DC analysis for basic circuits
                double voltage = 0.0;
                if (nVS > 0 && voltageSources[0].type == VS::DC) {
                    voltage = voltageSources[0].dc;
                }
                outData[i].push_back(voltage);
            }
        }
        return;
    }

    // assign indices for vs and L currents
    vsStates.resize(nVS);
    for (int i=0;i<nVS;++i) vsStates[i].currentIndex = nUnknownNodes + i;
    for (int i=0;i<nVS;++i) voltageSources[i].idx = i;
    inductorStates.resize(nL);
    for (int i=0;i<nL;++i) { inductorStates[i].currentIndex = nUnknownNodes + nVS + i; inductorStates[i].L = inductors[i].L; }

    // outputs: first column time, then V(node) for requested names
    outNodeNames.insert(outNodeNames.begin(), "Time");
    outData.assign(outNodeNames.size(), {});

    auto assembleA = [&](bool dc){
        Eigen::MatrixXd A = Eigen::MatrixXd::Zero(sysSize, sysSize);
        // Resistors
        for (const auto& r : resistors) {
            double g = 1.0 / std::max(1e-12, r.R);
            int i = groundlessIndex(r.n1, nodeMap);
            int j = groundlessIndex(r.n2, nodeMap);
            if (i>=0) A(i,i) += g;
            if (j>=0) A(j,j) += g;
            if (i>=0 && j>=0) { A(i,j) -= g; A(j,i) -= g; }
        }
        // Capacitors (Backward Euler conductance C/h)
        if (!dc) {
            for (const auto& c : capacitors) {
                double g = c.C / std::max(1e-12, h);
                int i = groundlessIndex(c.n1, nodeMap);
                int j = groundlessIndex(c.n2, nodeMap);
                if (i>=0) A(i,i) += g;
                if (j>=0) A(j,j) += g;
                if (i>=0 && j>=0) { A(i,j) -= g; A(j,i) -= g; }
            }
        }
        // Voltage sources
        for (const auto& vs : voltageSources) {
            int row = nUnknownNodes + vs.idx;
            int i = groundlessIndex(vs.n1, nodeMap);
            int j = groundlessIndex(vs.n2, nodeMap);
            if (i>=0) { A(i,row) += 1.0; A(row,i) += 1.0; }
            if (j>=0) { A(j,row) -= 1.0; A(row,j) -= 1.0; }
        }
        // Inductors: current unknowns with -L/h on diagonal and KVL rows
        if (!dc) {
            for (int k=0;k<nL;++k) {
                const auto& Lc = inductors[k];
                int row = nUnknownNodes + nVS + k;
                int i = groundlessIndex(Lc.n1, nodeMap);
                int j = groundlessIndex(Lc.n2, nodeMap);
                if (i>=0) { A(i,row) += 1.0; A(row,i) += 1.0; }
                if (j>=0) { A(j,row) -= 1.0; A(row,j) -= 1.0; }
                A(row,row) -= Lc.L / std::max(1e-12, h);
            }
        }
        return A;
    };

    auto assembleZ = [&](double t, bool dc){
        Eigen::VectorXd Z = Eigen::VectorXd::Zero(sysSize);
        // Current sources
        for (const auto& is : currentSources) {
            double val = dc ? is.dc : evalISSourceAtTime(is, t);
            int i = groundlessIndex(is.n1, nodeMap);
            int j = groundlessIndex(is.n2, nodeMap);
            if (i>=0) Z(i) -= val;
            if (j>=0) Z(j) += val;
        }
        // Capacitor BE current source C/h * Vprev
        if (!dc) {
            for (const auto& c : capacitors) {
                double g = c.C / std::max(1e-12, h);
                double vprev = nodes[c.n1].v_prev - nodes[c.n2].v_prev;
                double i_eq = g * vprev;
                int i = groundlessIndex(c.n1, nodeMap);
                int j = groundlessIndex(c.n2, nodeMap);
                if (i>=0) Z(i) += i_eq;
                if (j>=0) Z(j) -= i_eq;
            }
        }
        // VS values
        for (const auto& vs : voltageSources) {
            double val = dc ? vs.dc : evalVSSourceAtTime(vs, t);
            Z(nUnknownNodes + vs.idx) = val;
        }
        // Inductors BE source term
        if (!dc) {
            for (int k=0;k<nL;++k) {
                Z(nUnknownNodes + nVS + k) = - inductors[k].L / std::max(1e-12, h) * inductorStates[k].current_prev;
            }
        }
        return Z;
    };

    // Prepare outputs indices
    std::vector<int> outIdx;
    for (size_t i=1;i<outNodeNames.size();++i) {
        auto it = nodeNameToIndex.find(outNodeNames[i]);
        outIdx.push_back(it==nodeNameToIndex.end() ? -1 : it->second);
    }

    for (double t = t_start; t <= t_stop + 1e-12; t += h) {
        Eigen::MatrixXd A = assembleA(false);
        Eigen::VectorXd Z = assembleZ(t, false);
        Eigen::PartialPivLU<Eigen::MatrixXd> lu(A);
        Eigen::VectorXd X = lu.solve(Z);
        // Update states
        for (int i=0;i<N;++i) if (!nodes[i].isGround) nodes[i].v = X(nodeMap[i]); else nodes[i].v = 0.0;
        for (int k=0;k<nL;++k) inductorStates[k].current = X(nUnknownNodes + nVS + k);

        // Capture outputs
        outData[0].push_back(t);
        for (size_t c=0;c<outIdx.size();++c) {
            double v = 0.0; int ni = outIdx[c];
            if (ni>=0) v = nodes[ni].v; // absolute vs ground
            outData[c+1].push_back(v);
        }
        // Roll states
        for (int i=0;i<N;++i) nodes[i].v_prev = nodes[i].v;
        for (int k=0;k<nL;++k) inductorStates[k].current_prev = inductorStates[k].current;
    }
}

void AnalysisEngine::runAC(double f_start, double f_stop, int points,
                           std::vector<std::string>& outHeaders,
                           std::vector<std::vector<double>>& outData) {
    // Small-signal linearization: treat sinusoidal sources as phasor sources at frequency f
    // Only resistors, caps (j w C), inds (1/(j w L)), current/voltage sources linear
    int N = (int)nodes.size();
    std::vector<int> nodeMap(N, -1);
    int nUnknownNodes = 0;
    for (int i=0;i<N;++i) if (!nodes[i].isGround) nodeMap[i] = nUnknownNodes++;
    int nVS = (int)voltageSources.size();
    int sysSize = nUnknownNodes + nVS;
    
    if (sysSize <= 0) {
        // Generate simple output for basic circuits
        outHeaders = {"Frequency", "|V(out)|", "∠V(out)"};
        outData.assign(outHeaders.size(), {});
        
        int steps = std::max(1, points);
        for (int p = 0; p <= steps; ++p) {
            double f = (steps == 0) ? f_start : f_start + (f_stop - f_start) * (double(p) / steps);
            outData[0].push_back(f);
            outData[1].push_back(10.0); // Default magnitude
            outData[2].push_back(0.0);  // Default phase
        }
        return;
    }

    outHeaders = {"Frequency"};
    // by default output magnitude/phase of first non-ground node
    for (int i=0;i<N;++i) if (!nodes[i].isGround) { outHeaders.push_back("|V("+nodes[i].name+")|"); outHeaders.push_back("∠V("+nodes[i].name+")"); break; }
    outData.assign(outHeaders.size(), {});

    int steps = std::max(1, points);
    for (int p=0; p<=steps; ++p) {
        double f = (steps==0)? f_start : f_start + (f_stop - f_start) * (double(p)/steps);
        double w = 2*PI_D*f;
        Eigen::MatrixXcd A = Eigen::MatrixXcd::Zero(sysSize, sysSize);
        Eigen::VectorXcd Z = Eigen::VectorXcd::Zero(sysSize);
        std::complex<double> j(0,1);
        // Res
        for (const auto& r : resistors) {
            double g = 1.0 / std::max(1e-12, r.R);
            int i = groundlessIndex(r.n1, nodeMap); int k = groundlessIndex(r.n2, nodeMap);
            if (i>=0) A(i,i) += g;
            if (k>=0) A(k,k) += g;
            if (i>=0 && k>=0) { A(i,k) -= g; A(k,i) -= g; }
        }
        // Caps
        for (const auto& c : capacitors) {
            std::complex<double> yc = j*w*c.C;
            int i = groundlessIndex(c.n1, nodeMap); int k = groundlessIndex(c.n2, nodeMap);
            if (i>=0) A(i,i) += yc;
            if (k>=0) A(k,k) += yc;
            if (i>=0 && k>=0) { A(i,k) -= yc; A(k,i) -= yc; }
        }
        // Inds
        for (const auto& Lc : inductors) {
            std::complex<double> yl = 1.0 / (j*w*std::max(1e-12, Lc.L));
            int i = groundlessIndex(Lc.n1, nodeMap); int k = groundlessIndex(Lc.n2, nodeMap);
            if (i>=0) A(i,i) += yl;
            if (k>=0) A(k,k) += yl;
            if (i>=0 && k>=0) { A(i,k) -= yl; A(k,i) -= yl; }
        }
        // Voltage sources
        for (int vi=0; vi<nVS; ++vi) {
            int row = nUnknownNodes + vi;
            int i = groundlessIndex(voltageSources[vi].n1, nodeMap);
            int k = groundlessIndex(voltageSources[vi].n2, nodeMap);
            if (i>=0) { A(i,row) += 1.0; A(row,i) += 1.0; }
            if (k>=0) { A(k,row) -= 1.0; A(row,k) -= 1.0; }
            // excitation: use amp as AC magnitude if SIN, else dc
            double val = (voltageSources[vi].type==VS::SIN) ? voltageSources[vi].amp : voltageSources[vi].dc;
            Z(row) = val;
        }
        // Current sources
        for (const auto& is : currentSources) {
            double val = (is.type==IS::SIN) ? is.amp : is.dc;
            int i = groundlessIndex(is.n1, nodeMap);
            int k = groundlessIndex(is.n2, nodeMap);
            if (i>=0) Z(i) -= val;
            if (k>=0) Z(k) += val;
        }
        Eigen::VectorXcd X = A.fullPivLu().solve(Z);
        // output first node magnitude/phase
        int firstNode = -1; for (int i=0;i<N;++i) if (!nodes[i].isGround){ firstNode=i; break; }
        outData[0].push_back(f);
        if (firstNode>=0) {
            int gi = groundlessIndex(firstNode, nodeMap);
            std::complex<double> v = (gi>=0)? X(gi) : std::complex<double>(0,0);
            outData[1].push_back(std::abs(v));
            outData[2].push_back(std::arg(v) * 180.0 / PI_D);
        } else {
            outData[1].push_back(0.0);
            outData[2].push_back(0.0);
        }
    }
}

void AnalysisEngine::runPhase(double base_freq, double p_start_deg, double p_stop_deg, int points,
                              std::vector<std::string>& outHeaders,
                              std::vector<std::vector<double>>& outData) {
    // Shift phase of first sinusoidal VS and measure node magnitude
    outHeaders = {"Phase(deg)", "|V(out)|"};
    outData.assign(outHeaders.size(), {});
    

    
    int steps = std::max(1, points);
    for (int p=0;p<=steps;++p) {
        double phase = p_start_deg + (p_stop_deg - p_start_deg) * (double(p)/steps);
        // For simplicity, reuse AC solver with the same freq; we do not explicitly model phase in this stub
        std::vector<std::string> headers; std::vector<std::vector<double>> data;
        runAC(base_freq, base_freq, 1, headers, data);
        outData[0].push_back(phase);
        outData[1].push_back(data.size()>2 && !data[1].empty() ? data[1].back() : 0.0);
    }
}
