#include "zenerdiode.h"
#include <QApplication>
#include <QPalette>

ZenerDiodeView::ZenerDiodeView(std::shared_ptr<Element> element, QGraphicsItem *parent)
    : CircuitComponent(element, parent)
{
}

void ZenerDiodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    
    if (!logicElement || !logicElement->node1 || !logicElement->node2) return;
    
    // Get theme-aware colors
    const bool isDark = qApp->palette().window().color().lightness() < 128;
    const QColor componentColor = isDark ? QColor(255, 255, 255) : QColor(0, 0, 0);
    
    QPen pen(componentColor, 2);
    painter->setPen(pen);
    
    // Draw Zener diode symbol (similar to regular diode but with additional lines)
    QPointF p1(logicElement->node1->getX(), logicElement->node1->getY());
    QPointF p2(logicElement->node2->getX(), logicElement->node2->getY());
    
    // Calculate center and direction
    QPointF center = (p1 + p2) / 2.0;
    QPointF direction = p2 - p1;
    qreal length = std::sqrt(direction.x() * direction.x() + direction.y() * direction.y());
    
    if (length < 1e-6) return; // Avoid division by zero
    
    // Normalize direction
    direction /= length;
    
    // Perpendicular vector for width
    QPointF perp(-direction.y(), direction.x());
    const qreal width = 50.0;
    
    // Draw main diode body (triangle)
    QPolygonF triangle;
    triangle << center + perp * width/2;
    triangle << center - perp * width/2;
    triangle << center + direction * width/2;
    painter->drawPolygon(triangle);
    
    // Draw Zener-specific lines (additional lines on cathode side)
    QPointF cathode = center - direction * width/2;
    QPointF lineStart = cathode + perp * width/3;
    QPointF lineEnd = cathode - perp * width/3;
    painter->drawLine(lineStart, lineEnd);
    
    // Draw connection lines to nodes
    painter->drawLine(p1, center - direction * width/2);
    painter->drawLine(p2, center + direction * width/2);
}

QRectF ZenerDiodeView::boundingRect() const
{
    if (!logicElement || !logicElement->node1 || !logicElement->node2) return QRectF();
    
    QPointF p1(logicElement->node1->getX(), logicElement->node1->getY());
    QPointF p2(logicElement->node2->getX(), logicElement->node2->getY());
    QPointF center = (p1 + p2) / 2.0;
    
    return QRectF(center.x() - 60, center.y() - 60, 120, 120);
}
