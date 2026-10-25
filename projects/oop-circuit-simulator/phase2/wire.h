#ifndef WIRE_H
#define WIRE_H

#include <QGraphicsLineItem>
#include <QPointF>

class CircuitComponent; // Forward declaration

class Wire : public QGraphicsLineItem {
public:
    Wire(QGraphicsItem *parent = nullptr);

    // Methods to manage connections
    void setStartComponent(CircuitComponent *comp, const QPointF &connPoint);
    void setEndComponent(CircuitComponent *comp, const QPointF &connPoint);
    CircuitComponent* getStartComponent() const;
    CircuitComponent* getEndComponent() const;
    QPointF getStartConnectionPoint() const;
    QPointF getEndConnectionPoint() const;

    void updatePosition();

    // Methods for wire-to-wire connection logic
    bool isPointOnWire(const QPointF &point, QPointF &closestPointOnLine) const;
    void split(CircuitComponent* junction); // Crucial new function

private:
    CircuitComponent *startComponent;
    CircuitComponent *endComponent;
    QPointF startConnPoint;
    QPointF endConnPoint;
};

#endif // WIRE_H