#ifndef ZENERDIODE_H
#define ZENERDIODE_H

#include "circuitcomponent.h"
#include <QPainter>

class ZenerDiodeView : public CircuitComponent
{
public:
    explicit ZenerDiodeView(std::shared_ptr<Element> element, QGraphicsItem *parent = nullptr);
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};

#endif // ZENERDIODE_H
