#ifndef CURRENTSOURCEVIEW_H
#define CURRENTSOURCEVIEW_H

#include "circuitcomponent.h"

class CurrentSourceView : public CircuitComponent
{
public:
    CurrentSourceView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // CURRENTSOURCEVIEW_H


