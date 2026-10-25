#ifndef NODELABEL_H
#define NODELABEL_H

#include "circuitcomponent.h"

class NodeLabel : public CircuitComponent {
public:
    NodeLabel(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    ComponentType componentType() const override { return ComponentType::NodeLabel; }
    void serialize(QDataStream& stream) const override;

    // A function to set the label text and update the item
    void setLabel(const QString& text);

private:
    QString label;
};

#endif // NODELABEL_H