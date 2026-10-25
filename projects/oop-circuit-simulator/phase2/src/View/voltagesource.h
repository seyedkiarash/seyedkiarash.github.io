// =======================================================================
// =======================================================================
//
//   FILE: src/View/voltagesource.h (New File)
//
// =======================================================================
// =======================================================================

#ifndef VOLTAGESOURCEVIEW_H
#define VOLTAGESOURCEVIEW_H

#include "circuitcomponent.h"

class VoltageSourceView : public CircuitComponent
{
public:
    VoltageSourceView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // VOLTAGESOURCEVIEW_H

