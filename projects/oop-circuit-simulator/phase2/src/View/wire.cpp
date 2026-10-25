//
// Created by Asus on 8/19/2025.
//
// =======================================================================
// =======================================================================
//
//   FILE: src/View/wire.cpp (New File)
//
// =======================================================================
// =======================================================================

#include "wire.h"
#include <QPainter>

WireView::WireView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent)
    : CircuitComponent(elementLogic, parent)
{}

QRectF WireView::boundingRect() const
{
    if (!logicElement || !logicElement->node1 || !logicElement->node2) {
        return QRectF();
    }
    
    qreal x1 = logicElement->node1->getX();
    qreal y1 = logicElement->node1->getY();
    qreal x2 = logicElement->node2->getX();
    qreal y2 = logicElement->node2->getY();
    
    return QRectF(qMin(x1, x2) - 2, qMin(y1, y2) - 2, 
                 qAbs(x2 - x1) + 4, qAbs(y2 - y1) + 4);
}

void WireView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    if (!logicElement || !logicElement->node1 || !logicElement->node2) {
        return;
    }
    
    painter->setPen(QPen(Qt::white, 2));
    
    qreal x1 = logicElement->node1->getX();
    qreal y1 = logicElement->node1->getY();
    qreal x2 = logicElement->node2->getX();
    qreal y2 = logicElement->node2->getY();
    
    painter->drawLine(x1, y1, x2, y2);
}