// =======================================================================
// =======================================================================
//
//   FILE: src/View/inductor.h (New File)
//
// =======================================================================
// =======================================================================

#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "circuitcomponent.h"

class InductorView : public CircuitComponent
{
public:
    InductorView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // INDUCTOR_H
