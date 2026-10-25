// =======================================================================
// FILE: subcircuitview.cpp
// =======================================================================

#include "subcircuitview.h"
#include "../Core/datatypes.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>

SubCircuitView::SubCircuitView(std::shared_ptr<Element> element)
    : CircuitComponent(element)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void SubCircuitView::updateFromLogic()
{
    if (!logicElement) return;
    
    // Update position based on node positions
    if (logicElement->node1 && logicElement->node2) {
        double x1 = logicElement->node1->getX();
        double y1 = logicElement->node1->getY();
        double x2 = logicElement->node2->getX();
        double y2 = logicElement->node2->getY();
        
        // Center the component between the two nodes
        double centerX = (x1 + x2) / 2.0;
        double centerY = (y1 + y2) / 2.0;
        
        setPos(centerX - width/2, centerY - height/2);
    }
    
    update();
}

void SubCircuitView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    
    painter->setRenderHint(QPainter::Antialiasing);
    
    // Check if dark theme is active
    bool isDark = scene() && scene()->palette().window().color().lightness() < 128;
    QColor textColor = isDark ? QColor(255, 255, 255) : QColor(0, 0, 0);
    QColor borderColor = isDark ? QColor(200, 200, 200) : QColor(0, 0, 0);
    QColor fillColor = isDark ? QColor(50, 50, 50) : QColor(240, 240, 240);
    
    painter->setPen(QPen(borderColor, 2));
    painter->setBrush(QBrush(fillColor));
    
    // Draw main rectangle
    painter->drawRect(0, 0, width, height);
    
    // Draw subcircuit symbol (internal components representation)
    drawSubcircuitSymbol(painter);
    
    // Draw pin labels
    drawPinLabels(painter);
    
    // Draw component name
    painter->setPen(textColor);
    painter->setFont(QFont("Arial", 8));
    QString name = QString::fromStdString(logicElement->name);
    painter->drawText(QRectF(0, height - 20, width, 20), Qt::AlignCenter, name);
    
    // Draw "SUB" label
    painter->setFont(QFont("Arial", 10, QFont::Bold));
    painter->drawText(QRectF(0, 0, width, 30), Qt::AlignCenter, "SUB");
}

QRectF SubCircuitView::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void SubCircuitView::drawSubcircuitSymbol(QPainter *painter)
{
    // Draw a simplified representation of internal components
    painter->setPen(QPen(Qt::black, 1));
    
    // Draw some internal component symbols (simplified)
    // Resistor symbol
    painter->drawLine(20, 40, 30, 40);
    painter->drawLine(30, 40, 30, 35);
    painter->drawLine(30, 35, 35, 45);
    painter->drawLine(35, 45, 40, 35);
    painter->drawLine(40, 35, 45, 45);
    painter->drawLine(45, 45, 50, 35);
    painter->drawLine(50, 35, 55, 45);
    painter->drawLine(55, 45, 60, 40);
    painter->drawLine(60, 40, 70, 40);
    
    // Capacitor symbol
    painter->drawLine(80, 40, 90, 40);
    painter->drawLine(90, 40, 90, 30);
    painter->drawLine(90, 30, 90, 50);
    painter->drawLine(100, 40, 110, 40);
    painter->drawLine(110, 40, 110, 30);
    painter->drawLine(110, 30, 110, 50);
}

void SubCircuitView::drawPinLabels(QPainter *painter)
{
    painter->setPen(QPen(Qt::blue, 1));
    painter->setFont(QFont("Arial", 7));
    
    // Draw pin labels at the edges
    if (logicElement && logicElement->node1) {
        QString pin1Name = QString::fromStdString(logicElement->node1->getName());
        painter->drawText(QRectF(0, height/2 - 10, 20, 20), Qt::AlignCenter, pin1Name);
    }
    
    if (logicElement && logicElement->node2) {
        QString pin2Name = QString::fromStdString(logicElement->node2->getName());
        painter->drawText(QRectF(width - 20, height/2 - 10, 20, 20), Qt::AlignCenter, pin2Name);
    }
}
