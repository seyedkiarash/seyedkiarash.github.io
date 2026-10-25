#include "currentsource.h"
#include <QPainter>
#include <QApplication>
#include <QPalette>

CurrentSourceView::CurrentSourceView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent)
    : CircuitComponent(elementLogic, parent)
{}

QRectF CurrentSourceView::boundingRect() const
{
    return QRectF(-60, -30, 120, 60);
}

void CurrentSourceView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const bool isDark = qApp->palette().window().color().lightness() < 128;
    painter->setPen(QPen(isDark ? Qt::white : Qt::black, 2));
    painter->drawEllipse(QPointF(0, 0), 30, 30);
    painter->drawLine(-15, 0, 15, 0);
    painter->drawLine(15, 0, 10, -10);
    painter->drawLine(15, 0, 10, 10);
    painter->drawLine(-60, 0, -30, 0);
    painter->drawLine(30, 0, 60, 0);
    painter->drawText(boundingRect().adjusted(5, 0, 0, 0), Qt::AlignVCenter | Qt::AlignLeft, QString::fromStdString(logicElement->name));
}


