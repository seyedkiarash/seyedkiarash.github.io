#ifndef DIODEV_H
#define DIODEV_H

#include "circuitcomponent.h"

class DiodeView : public CircuitComponent
{
public:
    DiodeView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // DIODEV_H


