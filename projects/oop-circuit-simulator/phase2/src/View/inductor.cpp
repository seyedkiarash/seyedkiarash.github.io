// =======================================================================
// =======================================================================
//
//   FILE: src/View/inductor.cpp (New File)
//
// =======================================================================
// =======================================================================

#include "inductor.h"
#include <QPainter>
#include <QApplication>
#include <QPalette>

InductorView::InductorView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent)
    : CircuitComponent(elementLogic, parent)
{}

QRectF InductorView::boundingRect() const
{
    return QRectF(-55, -30, 110, 60);
}

void InductorView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const bool isDark = qApp->palette().window().color().lightness() < 128;
    painter->setPen(QPen(isDark ? Qt::white : Qt::black, 2));

    // رسم سلف به صورت سیم‌پیچ
    painter->drawLine(-50, 0, -30, 0);
    painter->drawArc(QRectF(-30, -15, 30, 30), 180 * 16, -180 * 16);
    painter->drawArc(QRectF(0, -15, 30, 30), 180 * 16, -180 * 16);
    painter->drawArc(QRectF(30, -15, 30, 30), 180 * 16, -180 * 16);
    painter->drawLine(60, 0, 50, 0);

    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignBottom, QString::fromStdString(logicElement->name));
}