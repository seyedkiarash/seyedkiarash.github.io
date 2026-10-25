// =======================================================================
// =======================================================================
//
//   FILE: src/View/capacitor.cpp (New File)
//
// =======================================================================
// =======================================================================

#include "capacitor.h"
#include <QPainter>
#include <QApplication>
#include <QPalette>

CapacitorView::CapacitorView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent)
    : CircuitComponent(elementLogic, parent)
{}

QRectF CapacitorView::boundingRect() const
{
    return QRectF(-55, -30, 110, 60);
}

void CapacitorView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const bool isDark = qApp->palette().window().color().lightness() < 128;
    painter->setPen(QPen(isDark ? Qt::white : Qt::black, 2));

    // رسم سیم و صفحه سمت چپ
    painter->drawLine(-50, 0, -20, 0);
    painter->drawLine(-20, -25, -20, 25);

    // رسم سیم و صفحه سمت راست
    painter->drawLine(20, 0, 50, 0);
    painter->drawLine(20, -25, 20, 25);

    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignBottom, QString::fromStdString(logicElement->name));
}