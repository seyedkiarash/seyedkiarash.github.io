// =======================================================================
// =======================================================================
//
//   FILE: src/View/wire.h (New File)
//
// =======================================================================
// =======================================================================

#ifndef WIRE_H
#define WIRE_H

#include "circuitcomponent.h"
#include <QGraphicsItem>

class WireView : public CircuitComponent
{
public:
    WireView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // WIRE_H

