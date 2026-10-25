//
// Created by Asus on 8/19/2025.
//
// =======================================================================
// =======================================================================
//
//   FILE: src/View/circuitcomponent.cpp (New File)
//
// =======================================================================
// =======================================================================

#include "circuitcomponent.h"

CircuitComponent::CircuitComponent(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent)
    : QGraphicsObject(parent), logicElement(elementLogic)
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

std::shared_ptr<Element> CircuitComponent::getLogicElement() const
{
    return logicElement;
}

void CircuitComponent::updateFromLogic()
{
    if (!logicElement || !logicElement->node1 || !logicElement->node2) return;

    // موقعیت المان گرافیکی را در وسط دو گره منطقی قرار می‌دهیم
    QPointF p1(logicElement->node1->getX(), logicElement->node1->getY());
    QPointF p2(logicElement->node2->getX(), logicElement->node2->getY());
    setPos((p1 + p2) / 2.0);
}
