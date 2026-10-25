#include "graphicsview.h"
#include "../Core/datatypes.h"
#include "resistor.h"
#include "capacitor.h"
#include "inductor.h"
#include "voltagesource.h"
#include "currentsource.h"
#include "diode.h"
#include "zenerdiode.h"
#include "ground.h"
#include "wire.h"
#include "subcircuitview.h"
#include <QCursor>
#include <QtMath>

void GraphicsView::startPlacing(const QString& logicalType)
{
    if (!circuitModel) {
        qDebug() << "GraphicsView::startPlacing: circuitModel is null!";
        return;
    }
    
    try {
        cancelPlacing();
        placingActive = true;
        placingType = logicalType;
        rotationAngleDeg = 0.0;
        setFocus();

        if (logicalType == "Resistor") {
            qDebug() << "Creating Resistor...";
            previewElementLogic = std::make_shared<Resistor>();
        }
    else if (logicalType == "Capacitor") {
        qDebug() << "Creating Capacitor...";
        previewElementLogic = std::make_shared<Capacitor>();
    }
    else if (logicalType == "Inductor") {
        qDebug() << "Creating Inductor...";
        previewElementLogic = std::make_shared<Inductor>();
    }
    else if (logicalType == "VoltageSource" || logicalType == "Voltage" || logicalType == "VoltageSourceDC") {
        qDebug() << "Creating VoltageSourceDC...";
        previewElementLogic = std::make_shared<VoltageSourceDC>();
        qDebug() << "VoltageSourceDC created successfully";
    }
    else if (logicalType == "VoltageSourceSinusoidal" || logicalType == "VoltageSin" || logicalType == "Sinusoidal") previewElementLogic = std::make_shared<VoltageSourceSin>();
    else if (logicalType == "VoltageSourcePulse" || logicalType == "VoltagePulse" || logicalType == "Pulse") previewElementLogic = std::make_shared<VoltageSourcePulse>();
    else if (logicalType == "CurrentSource" || logicalType == "Current" || logicalType == "CurrentSourceDC") previewElementLogic = std::make_shared<CurrentSourceDC>();
    else if (logicalType == "CurrentSourceSin" || logicalType == "CurrentSin") previewElementLogic = std::make_shared<CurrentSourceSin>();
    else if (logicalType == "CurrentSourcePulse" || logicalType == "CurrentPulse") previewElementLogic = std::make_shared<CurrentSourcePulse>();
    else if (logicalType == "Diode") previewElementLogic = std::make_shared<Diode>();
    else if (logicalType == "ZenerDiode" || logicalType == "Zener") previewElementLogic = std::make_shared<ZenerDiode>();
    else if (logicalType == "Ground" || logicalType == "GND") previewElementLogic = std::make_shared<Ground>();
    else if (logicalType == "SubCircuit") {
        // For SubCircuit, we need to find the existing one in the project
        // and use it for placement
        if (circuitModel) {
            const auto& elements = circuitModel->getProjectData().elements;
            for (const auto& elem : elements) {
                if (elem && elem->getType() == "SubCircuit") {
                    previewElementLogic = elem;
                    break;
                }
            }
        }
        if (!previewElementLogic) {
            previewElementLogic = std::make_shared<SubCircuit>();
        }
    }
    else previewElementLogic.reset();

    if (previewElementLogic) {
        previewElementLogic->name = generateUniqueElementName(logicalType).toStdString();
        
        // Special handling for Ground: only one node
        if (logicalType == "Ground" || logicalType == "GND") {
            previewElementLogic->node1 = std::make_shared<Node>(generateUniqueNodeName().toStdString());
            previewElementLogic->node2 = previewElementLogic->node1; // Same node for both terminals
        } else {
            previewElementLogic->node1 = std::make_shared<Node>(generateUniqueNodeName().toStdString());
            previewElementLogic->node2 = std::make_shared<Node>(generateUniqueNodeName().toStdString());
        }

        if (dynamic_cast<Resistor*>(previewElementLogic.get())) previewGraphics = new ResistorView(previewElementLogic);
        else if (dynamic_cast<Capacitor*>(previewElementLogic.get())) previewGraphics = new CapacitorView(previewElementLogic);
        else if (dynamic_cast<Inductor*>(previewElementLogic.get())) previewGraphics = new InductorView(previewElementLogic);
        else if (dynamic_cast<VoltageSource*>(previewElementLogic.get())) previewGraphics = new VoltageSourceView(previewElementLogic);
        else if (dynamic_cast<CurrentSource*>(previewElementLogic.get())) previewGraphics = new CurrentSourceView(previewElementLogic);
        else if (dynamic_cast<Diode*>(previewElementLogic.get())) previewGraphics = new DiodeView(previewElementLogic);
        else if (dynamic_cast<ZenerDiode*>(previewElementLogic.get())) previewGraphics = new ZenerDiodeView(previewElementLogic);
        else if (dynamic_cast<Ground*>(previewElementLogic.get())) previewGraphics = new GroundView(previewElementLogic);
        else if (dynamic_cast<SubCircuit*>(previewElementLogic.get())) previewGraphics = new SubCircuitView(previewElementLogic);

        if (previewGraphics) {
            previewGraphics->setOpacity(0.6);
            scene->addItem(previewGraphics);
            QPoint globalPos = QCursor::pos();
            QPoint viewPos = mapFromGlobal(globalPos);
            updatePreviewAt(mapToScene(viewPos));
        }
    }
    } catch (const std::exception& e) {
        qDebug() << "GraphicsView::startPlacing exception:" << e.what();
        placingActive = false;
        placingType.clear();
        previewElementLogic.reset();
        if (previewGraphics) { 
            scene->removeItem(previewGraphics); 
            delete previewGraphics; 
            previewGraphics = nullptr; 
        }
    } catch (...) {
        qDebug() << "GraphicsView::startPlacing unknown exception";
        placingActive = false;
        placingType.clear();
        previewElementLogic.reset();
        if (previewGraphics) { 
            scene->removeItem(previewGraphics); 
            delete previewGraphics; 
            previewGraphics = nullptr; 
        }
    }
}

void GraphicsView::cancelPlacing()
{
    placingActive = false;
    placingType.clear();
    previewElementLogic.reset();
    if (previewGraphics) { scene->removeItem(previewGraphics); delete previewGraphics; previewGraphics = nullptr; }
    unsetCursor();
}

void GraphicsView::updatePreviewAt(const QPointF& scenePos)
{
    if (!previewElementLogic || !previewGraphics) return;
    QPointF center = snapEnabled ? snapToGrid(scenePos) : scenePos;
    
    if (placingType == "Ground" || placingType == "GND") {
        // Ground is placed at cursor position, no rotation needed
        previewElementLogic->node1 = std::make_shared<Node>(previewElementLogic->node1->getName(), center.x(), center.y());
        previewElementLogic->node2 = previewElementLogic->node1; // Same node for both terminals
    } else {
        // Normal components: compute endpoints based on rotation
        double radians = qDegreesToRadians(rotationAngleDeg);
        const double halfSpan = 60.0; // Increased to match larger component sizes
        double dx = halfSpan * std::cos(radians);
        double dy = halfSpan * std::sin(radians);
        QPointF p1(center.x() - dx, center.y() - dy);
        QPointF p2(center.x() + dx, center.y() + dy);
        previewElementLogic->node1 = std::make_shared<Node>(previewElementLogic->node1->getName(), p1.x(), p1.y());
        previewElementLogic->node2 = std::make_shared<Node>(previewElementLogic->node2->getName(), p2.x(), p2.y());
    }
    
    previewGraphics->updateFromLogic();
}

void GraphicsView::commitPlacementAt(const QPointF& scenePos)
{
    if (!circuitModel || !previewElementLogic) return;
    updatePreviewAt(scenePos);

    auto &proj = circuitModel->getProjectData();
    
    // Special handling for Ground: only create one node at the placement position
    if (placingType == "Ground") {
        // Create single ground node at placement position
        auto groundNode = std::make_shared<Node>("0", previewElementLogic->node1->getX(), previewElementLogic->node1->getY());
        proj.nodes.push_back(groundNode);
        
        // Create ground element with single node
        auto ground = std::make_shared<Ground>();
        ground->name = "GND";
        ground->node1 = groundNode;
        ground->node2 = groundNode; // Ground uses same node for both terminals
        proj.elements.push_back(ground);
    } else {
        // Normal components: add both nodes and element
        proj.nodes.push_back(previewElementLogic->node1);
        proj.nodes.push_back(previewElementLogic->node2);
        proj.elements.push_back(previewElementLogic);
    }

    // Add element to subcircuit if in creation mode
    if (subcircuitCreationMode) {
        addElementToSubcircuit(previewElementLogic);
    }

    if (previewGraphics) { scene->removeItem(previewGraphics); delete previewGraphics; previewGraphics = nullptr; }
    previewElementLogic.reset();
    placingActive = false;
    placingType.clear();
    unsetCursor();
    updateView();
}
