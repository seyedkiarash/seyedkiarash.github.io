// =======================================================================
// =======================================================================
//
//   FILE: src/View/voltagesource.cpp (New File)
//
// =======================================================================
// =======================================================================

#include "voltagesource.h"
#include <QPainter>
#include <QApplication>
#include <QPalette>

VoltageSourceView::VoltageSourceView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent)
    : CircuitComponent(elementLogic, parent)
{}

QRectF VoltageSourceView::boundingRect() const
{
    // این المان به صورت افقی رسم می‌شود
    return QRectF(-60, -30, 120, 60);
}

void VoltageSourceView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const bool isDark = qApp->palette().window().color().lightness() < 128;
    painter->setPen(QPen(isDark ? Qt::white : Qt::black, 2));

    // رسم دایره
    painter->drawEllipse(QPointF(0, 0), 30, 30);

    // رسم علامت + و -
    painter->drawLine(-15, -12, -15, 12); // مثبت
    painter->drawLine(-25, 0, -5, 0);
    painter->drawLine(15, -12, 15, 12);   // منفی

    // رسم سیم‌های اتصال چپ و راست
    painter->drawLine(-60, 0, -30, 0);
    painter->drawLine(30, 0, 60, 0);

    painter->drawText(boundingRect().adjusted(5, 0, 0, 0), Qt::AlignVCenter | Qt::AlignLeft, QString::fromStdString(logicElement->name));
}

