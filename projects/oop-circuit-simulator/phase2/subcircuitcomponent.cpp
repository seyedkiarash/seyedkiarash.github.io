#include "subcircuitcomponent.h"
#include "resistor.h" // Include all possible internal components
#include "capacitor.h"
#include "inductor.h"
#include "voltagesource.h"
#include <QFileInfo>
#include <QPainter>
#include <QFile>
#include <QTextStream>

SubcircuitComponent::SubcircuitComponent(QGraphicsItem *parent) : CircuitComponent(parent) {
    name = "Sub1";
    componentTypeString = "Subcircuit";
    // Define the two external connection ports for the subcircuit "box"
    addConnectionPoint(QPointF(-40, 0)); // Port 1 (Left)
    addConnectionPoint(QPointF(40, 0));  // Port 2 (Right)
}

QRectF SubcircuitComponent::boundingRect() const {
    return QRectF(-45, -25, 90, 50);
}

void SubcircuitComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::white);

    // Draw the rectangle "box" for the subcircuit
    painter->drawRect(QRectF(-40, -20, 80, 40));
    painter->drawText(boundingRect(), Qt::AlignCenter, name);

    // Draw connection stubs
    painter->drawLine(-45, 0, -40, 0);
    painter->drawLine(40, 0, 45, 0);

    if (isSelected()) {
        drawConnectionPoints(painter);
    }
}

// THIS IS THE NEW, CRUCIAL FUNCTION
bool SubcircuitComponent::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    // This part is for LOGIC, not for drawing. It would be used by the simulator.
    // For now, we just need the name for the graphical representation.
    QFileInfo fileInfo(filePath);
    setName(fileInfo.baseName());

    return true;
}