// =======================================================================
// =======================================================================
//
//   FILE: src/View/resistor.h (New File)
//
// =======================================================================
// =======================================================================

#ifndef RESISTOR_H
#define RESISTOR_H

#include "circuitcomponent.h"

class ResistorView : public CircuitComponent
{
public:
    ResistorView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // RESISTOR_H