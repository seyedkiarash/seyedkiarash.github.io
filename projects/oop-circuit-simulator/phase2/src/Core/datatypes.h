// =======================================================================
// =======================================================================
//
//   FILE: src/Core/datatypes.h (FIXED)
//
// =======================================================================
// =======================================================================

#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include "cereal/types/polymorphic.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/memory.hpp"

class Node {
private:
    std::string name;
    double voltage = 0.0;
    double x = 0.0, y = 0.0;

public:
    Node(const std::string& n = "", double posX = 0.0, double posY = 0.0)
        : name(n), x(posX), y(posY) {}

    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }
    double getVoltage() const { return voltage; }
    void setVoltage(double v) { voltage = v; }

    // --- FIX: Added missing getter methods ---
    double getX() const { return x; }
    double getY() const { return y; }

    template<class Archive>
    void serialize(Archive & ar) {
        ar(name, voltage, x, y);
    }
};

class Element {
public:
    virtual ~Element() = default;
    std::string name;
    std::shared_ptr<Node> node1, node2;
    virtual std::string getType() const = 0;
    template<class Archive>
    void serialize(Archive & ar) { ar(name, node1, node2); }
};
class SubCircuit : public Element {
public:
    // Elements and nodes inside this subcircuit definition
    std::vector<std::shared_ptr<Element>> internalElements;
    std::vector<std::shared_ptr<Node>> internalNodes;
    // Indices into internalNodes that indicate external pins (for now, 2 pins)
    std::vector<int> pinNodeIndices; // size can be 2, or more for future

    std::string getType() const override { return "SubCircuit"; }
    template<class Archive>
    void serialize(Archive & ar) {
        ar(cereal::base_class<Element>(this), internalElements, internalNodes, pinNodeIndices);
    }
};
class Resistor : public Element {
public:
    double resistance;
    std::string getType() const override { return "Resistor"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<Element>(this), resistance); }
};
class Capacitor : public Element {
public:
    double capacitance;
    std::string getType() const override { return "Capacitor"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<Element>(this), capacitance); }
};
class Inductor : public Element {
public:
    double inductance;
    double current = 0.0;
    std::string getType() const override { return "Inductor"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<Element>(this), inductance, current); }
};
class VoltageSource : public Element {
public:
    double voltage;
    std::string getType() const override { return "VoltageSource"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<Element>(this), voltage); }
};

// Extended sources and devices for schematic placement
class VoltageSourceDC : public VoltageSource {
public:
    std::string getType() const override { return "VoltageSourceDC"; }
};
class VoltageSourceSin : public VoltageSource {
public:
    // amplitude, freq, phase ... kept minimal for view
    double amplitude = 1.0;
    double frequency = 1000.0;
    std::string getType() const override { return "VoltageSourceSin"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<VoltageSource>(this), amplitude, frequency); }
};
class VoltageSourcePulse : public VoltageSource {
public:
    std::string getType() const override { return "VoltageSourcePulse"; }
};

class CurrentSource : public Element {
public:
    double current = 0.0;
    std::string getType() const override { return "CurrentSource"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<Element>(this), current); }
};
class CurrentSourceDC : public CurrentSource {
public:
    std::string getType() const override { return "CurrentSourceDC"; }
};
class CurrentSourceSin : public CurrentSource {
public:
    double amplitude = 1.0;
    double frequency = 1000.0;
    std::string getType() const override { return "CurrentSourceSin"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<CurrentSource>(this), amplitude, frequency); }
};
class CurrentSourcePulse : public CurrentSource {
public:
    std::string getType() const override { return "CurrentSourcePulse"; }
};

class Diode : public Element {
public:
    std::string model;
    std::string getType() const override { return "Diode"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<Element>(this), model); }
};
class ZenerDiode : public Diode {
public:
    double breakdownVoltage = 5.1;
    std::string getType() const override { return "ZenerDiode"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<Diode>(this), breakdownVoltage); }
};

class Ground : public Element {
public:
    // only node1 is used
    std::string getType() const override { return "Ground"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<Element>(this)); }
};

class Wire : public Element {
public:
    std::string getType() const override { return "Wire"; }
    template<class Archive>
    void serialize(Archive & ar) { ar(cereal::base_class<Element>(this)); }
};

CEREAL_REGISTER_TYPE(Resistor);
CEREAL_REGISTER_TYPE(Capacitor);
CEREAL_REGISTER_TYPE(Inductor);
CEREAL_REGISTER_TYPE(VoltageSource);
CEREAL_REGISTER_TYPE(SubCircuit);
CEREAL_REGISTER_TYPE(VoltageSourceDC);
CEREAL_REGISTER_TYPE(VoltageSourceSin);
CEREAL_REGISTER_TYPE(VoltageSourcePulse);
CEREAL_REGISTER_TYPE(CurrentSource);
CEREAL_REGISTER_TYPE(CurrentSourceDC);
CEREAL_REGISTER_TYPE(CurrentSourceSin);
CEREAL_REGISTER_TYPE(CurrentSourcePulse);
CEREAL_REGISTER_TYPE(Diode);
CEREAL_REGISTER_TYPE(ZenerDiode);
CEREAL_REGISTER_TYPE(Ground);
CEREAL_REGISTER_TYPE(Wire);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, Resistor)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, Capacitor)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, Inductor)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, VoltageSource)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, SubCircuit)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, VoltageSourceDC)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, VoltageSourceSin)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, VoltageSourcePulse)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, CurrentSource)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, CurrentSourceDC)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, CurrentSourceSin)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, CurrentSourcePulse)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, Diode)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, ZenerDiode)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, Ground)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Element, Wire)

struct SimulationSettings {
    enum AnalysisType { Transient, AC, Phase };
    AnalysisType type = Transient;
    double t_stop = 1e-3;
    double t_start = 0.0;
    double t_step = 1e-6;
    enum SweepType { Linear, Octave, Decade };
    SweepType sweepType = Linear;
    double f_start = 1, f_stop = 1e6;
    int points = 100;
    double base_freq = 1000;
    double p_start = 0, p_stop = 360;
    int points_phase = 100;

    template<class Archive>
    void serialize(Archive & ar) {
        ar(type, t_stop, t_start, t_step, sweepType, f_start, f_stop, points, base_freq, p_start, p_stop, points_phase);
    }
};

class Project {
public:
    std::vector<std::shared_ptr<Element>> elements;
    std::vector<std::shared_ptr<Node>> nodes;
    SimulationSettings settings;
    std::string lastAnalysisResultPath;
    void clear() {
        elements.clear();
        nodes.clear();
        lastAnalysisResultPath.clear();
    }
    template<class Archive>
    void serialize(Archive & ar) {
        ar(elements, nodes, settings, lastAnalysisResultPath);
    }
};

#endif // DATATYPES_H