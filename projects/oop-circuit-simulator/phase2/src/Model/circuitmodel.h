// =======================================================================
// FILE: circuitmodel.h
// =======================================================================
// این لایه Model است. این کلاس منطق اصلی تحلیل مدار را در خود دارد.
// این کلاس هیچ وابستگی به Qt یا رابط کاربری ندارد.
//========================================================================
#ifndef CIRCUITMODEL_H
#define CIRCUITMODEL_H

#include "datatypes.h"
#include <string>
#include <fstream>

class AnalysisEngine;

class CircuitModel {
public:
    CircuitModel();
    Project& getProjectData();

    bool runAnalysis(const SimulationSettings& settings, const std::string& outputFilePath);

private:
    Project project;

    bool runTransientAnalysis(const SimulationSettings& settings, std::ofstream& outFile);
    bool runAcAnalysis(const SimulationSettings& settings, std::ofstream& outFile);
    bool runPhaseAnalysis(const SimulationSettings& settings, std::ofstream& outFile);

    void buildAnalysisEngine(AnalysisEngine& engine) const;
};

#endif // CIRCUITMODEL_H
