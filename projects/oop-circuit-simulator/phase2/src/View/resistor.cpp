//
// Created by Asus on 8/19/2025.
//
// =======================================================================
// =======================================================================
//
//   FILE: src/View/resistor.cpp (New File)
//
// =======================================================================
// =======================================================================

#include "resistor.h"
#include <QPainter>
#include <QApplication>
#include <QPalette>

ResistorView::ResistorView(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent)
    : CircuitComponent(elementLogic, parent)
{}

QRectF ResistorView::boundingRect() const
{
    return QRectF(-60, -25, 120, 50);
}

void ResistorView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    const bool isDark = qApp->palette().window().color().lightness() < 128;
    painter->setPen(QPen(isDark ? Qt::white : Qt::black, 2));

    // رسم مقاومت به صورت زیگزاگ
    QPainterPath path;
    path.moveTo(-55, 0);
    path.lineTo(-35, 0);
    path.lineTo(-20, -22);
    path.lineTo(0, 22);
    path.lineTo(20, -22);
    path.lineTo(35, 0);
    path.lineTo(55, 0);
    painter->drawPath(path);

    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignBottom, QString::fromStdString(logicElement->name));
}


// ... (فایل‌های capacitor.h/cpp, inductor.h/cpp, voltagesource.h/cpp به همین ترتیب اضافه می‌شوند) ...
// (برای اختصار، فقط Resistor به عنوان نمونه آورده شده است)

