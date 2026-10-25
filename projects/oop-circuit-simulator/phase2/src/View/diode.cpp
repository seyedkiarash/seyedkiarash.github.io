#include "diode.h"
#include <QPainter>
#include <QApplication>
#include <QPalette>

DiodeView::DiodeView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent)
    : CircuitComponent(elementLogic, parent)
{}

QRectF DiodeView::boundingRect() const { return QRectF(-60, -25, 120, 50); }

void DiodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option); Q_UNUSED(widget);
    const bool isDark = qApp->palette().window().color().lightness() < 128;
    painter->setPen(QPen(isDark ? Qt::white : Qt::black, 2));
    // مثلث و خط کاتد →
    painter->drawLine(-55, 0, -20, 0);
    QPolygonF tri; tri << QPointF(-20, -22) << QPointF(-20, 22) << QPointF(20, 0);
    painter->drawPolygon(tri);
    painter->drawLine(20, -22, 20, 22);
    painter->drawLine(20, 0, 55, 0);
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignBottom, QString::fromStdString(logicElement->name));
}


