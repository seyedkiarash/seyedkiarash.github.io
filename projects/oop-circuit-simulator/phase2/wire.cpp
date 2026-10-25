#include "wire.h"
#include "circuitcomponent.h"
#include <QPen>
#include <QGraphicsScene>
#include <cmath>

Wire::Wire(QGraphicsItem *parent)
        : QGraphicsLineItem(parent), startComponent(nullptr), endComponent(nullptr) {
    setPen(QPen(Qt::black, 2));
    setZValue(-1); // Draw wires behind components
}

void Wire::setStartComponent(CircuitComponent *comp, const QPointF &connPoint) {
    startComponent = comp;
    startConnPoint = connPoint;
    updatePosition();
}

void Wire::setEndComponent(CircuitComponent *comp, const QPointF &connPoint) {
    endComponent = comp;
    endConnPoint = connPoint;
    updatePosition();
}

CircuitComponent* Wire::getStartComponent() const { return startComponent; }
CircuitComponent* Wire::getEndComponent() const { return endComponent; }
QPointF Wire::getStartConnectionPoint() const { return startConnPoint; }
QPointF Wire::getEndConnectionPoint() const { return endConnPoint; }

void Wire::updatePosition() {
    if (startComponent && endComponent) {
        QPointF p1 = startComponent->mapToScene(startConnPoint);
        QPointF p2 = endComponent->mapToScene(endConnPoint);
        setLine(QLineF(p1, p2));
    }
}

bool Wire::isPointOnWire(const QPointF &point, QPointF &closestPointOnLine) const {
    const double tolerance = 6.0; // How close the click must be
    QLineF l = line();
    double len = l.length();
    if (len == 0) return false;

    double dx = l.dx();
    double dy = l.dy();

    double t = ((point.x() - l.x1()) * dx + (point.y() - l.y1()) * dy) / (len * len);

    if (t < 0) closestPointOnLine = l.p1();
    else if (t > 1) closestPointOnLine = l.p2();
    else closestPointOnLine = l.pointAt(t);

    return QLineF(point, closestPointOnLine).length() < tolerance;
}

// This function splits the current wire by connecting it to a junction
// and creating a new wire from the junction to the original endpoint.
void Wire::split(CircuitComponent *junction) {
    if (!scene() || !endComponent) return;

    // Create the new wire that will complete the split connection
    auto *newWire = new Wire();
    newWire->setStartComponent(junction, QPointF(0,0));
    newWire->setEndComponent(endComponent, endConnPoint);
    scene()->addItem(newWire);

    // Register the new wire with the components
    junction->addConnection(newWire);
    endComponent->removeConnection(this); // Remove old wire connection
    endComponent->addConnection(newWire);

    // Reroute this existing wire to end at the junction
    setEndComponent(junction, QPointF(0,0));
    junction->addConnection(this);
}