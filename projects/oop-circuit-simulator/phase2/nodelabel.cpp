#include "nodelabel.h"
#include <QPainter>

NodeLabel::NodeLabel(QGraphicsItem *parent) : CircuitComponent(parent) {
    labelName = "V_out"; // Default name
}

void NodeLabel::setLabelName(const QString &name) {
    labelName = name;
    update(); // Force a redraw to show the new name
}

QString NodeLabel::getLabelName() const {
    return labelName;
}

void NodeLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Draw the label's connection line and its name
    painter->setPen(QPen(Qt::darkGreen, 2));
    painter->drawLine(0, 0, 0, 20); // The "stem" of the label

    // Draw the text
    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignCenter, labelName);
}

QRectF NodeLabel::boundingRect() const {
    return QRectF(-30, -20, 60, 40);
}