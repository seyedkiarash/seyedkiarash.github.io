#ifndef GROUNDVIEW_H
#define GROUNDVIEW_H

#include "circuitcomponent.h"

class GroundView : public CircuitComponent
{
public:
    GroundView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // GROUNDVIEW_H


