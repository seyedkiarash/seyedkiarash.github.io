#include "ground.h"
#include <QPainter>
#include <QApplication>
#include <QPalette>

GroundView::GroundView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent)
    : CircuitComponent(elementLogic, parent)
{}

QRectF GroundView::boundingRect() const { return QRectF(-30, -15, 60, 45); }

void GroundView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    const bool isDark = qApp->palette().window().color().lightness() < 128;
    painter->setPen(QPen(isDark ? Qt::white : Qt::black, 2));
    // سیم ورودی
    painter->drawLine(0, -15, 0, 0);
    // سه خط زمین
    painter->drawLine(-25, 0, 25, 0);
    painter->drawLine(-20, 10, 20, 10);
    painter->drawLine(-15, 20, 15, 20);
}


