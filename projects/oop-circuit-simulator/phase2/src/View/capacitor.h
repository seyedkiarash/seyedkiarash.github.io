// =======================================================================
// =======================================================================
//
//   FILE: src/View/capacitor.h (New File)
//
// =======================================================================
// =======================================================================

#ifndef CAPACITOR_H
#define CAPACITOR_H

#include "circuitcomponent.h"

class CapacitorView : public CircuitComponent
{
public:
    CapacitorView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // CAPACITOR_H