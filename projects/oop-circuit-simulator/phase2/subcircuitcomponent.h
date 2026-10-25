#ifndef SUBCIRCUITCOMPONENT_H
#define SUBCIRCUITCOMPONENT_H

#include "circuitcomponent.h"

class SubcircuitComponent : public CircuitComponent {
public:
    SubcircuitComponent(QGraphicsItem *parent = nullptr);

    // Function to load the internal components from a file
    bool loadFromFile(const QString& filePath);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    ComponentType getComponentType() const override { return ComponentType::Subcircuit; }

private:
    QList<CircuitComponent*> internalComponents;
    QPointF port1, port2;
};

#endif // SUBCIRCuiTCOMPONENT_H