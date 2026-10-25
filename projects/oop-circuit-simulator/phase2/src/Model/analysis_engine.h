#ifndef ANALYSIS_ENGINE_H
#define ANALYSIS_ENGINE_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <complex>
#include "Eigen/Dense"

struct AE_Node {
    std::string name;
    double v = 0.0;
    double v_prev = 0.0;
    bool isGround = false;
};

struct AE_InductorState {
    int currentIndex = -1; // index in unknowns for inductor current (transient)
    double current = 0.0;
    double current_prev = 0.0;
    double L = 0.0;
};

struct AE_VoltageSourceState {
    int currentIndex = -1; // index in unknowns for voltage source current
    double value = 0.0;
};

class AnalysisEngine {
public:
    // Element definitions (simple)
    struct Res { int n1, n2; double R; };
    struct Cap { int n1, n2; double C; };
    struct Ind { int n1, n2; double L; int idx; }; // idx to AE_InductorState vector
    struct VS  { int n1, n2; int idx; enum Type { DC, SIN, PULSE } type = DC; double dc=0, amp=0, freq=0; };
    struct IS  { int n1, n2; enum Type { DC, SIN, PULSE } type = DC; double dc=0, amp=0, freq=0; };

    // Topology
    std::vector<AE_Node> nodes; // index of ground may be omitted from unknowns
    std::map<std::string,int> nodeNameToIndex;

    // Elements
    std::vector<Res> resistors;
    std::vector<Cap> capacitors;
    std::vector<Ind> inductors;
    std::vector<AE_InductorState> inductorStates;
    std::vector<VS> voltageSources;
    std::vector<AE_VoltageSourceState> vsStates;
    std::vector<IS> currentSources;

    // Build/manage
    int ensureNode(const std::string& name, bool isGroundName=false);

    // Transient
    void runTransient(double t_start, double t_stop, double h,
                      std::vector<std::string>& outNodeNames,
                      std::vector<std::vector<double>>& outTimeAndSeries);

    // AC sweep (linear small-signal): use sin sources as AC excitations at amplitude
    void runAC(double f_start, double f_stop, int points,
               std::vector<std::string>& outHeaders,
               std::vector<std::vector<double>>& outData);

    // Phase sweep at base frequency for first sinusoidal source; phase 0..360
    void runPhase(double base_freq, double p_start_deg, double p_stop_deg, int points,
                  std::vector<std::string>& outHeaders,
                  std::vector<std::vector<double>>& outData);

private:
    // Helpers
    bool isGroundName(const std::string& n) const;
    int groundlessIndex(int nodeIdx, const std::vector<int>& nodeMap) const;
    double evalVSSourceAtTime(const VS& vs, double t) const;
    double evalISSourceAtTime(const IS& is, double t) const;
};

#endif // ANALYSIS_ENGINE_H
