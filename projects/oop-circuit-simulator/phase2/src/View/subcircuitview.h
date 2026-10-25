// =======================================================================
// FILE: subcircuitview.h
// =======================================================================

#ifndef SUBCIRCUITVIEW_H
#define SUBCIRCUITVIEW_H

#include "circuitcomponent.h"
#include <QGraphicsItem>
#include <QPainter>
#include <memory>

class SubCircuitView : public CircuitComponent {
    Q_OBJECT

public:
    explicit SubCircuitView(std::shared_ptr<Element> element);
    ~SubCircuitView() override = default;

    void updateFromLogic();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

private:
    void drawSubcircuitSymbol(QPainter *painter);
    void drawPinLabels(QPainter *painter);
    
    static constexpr qreal width = 120.0;
    static constexpr qreal height = 80.0;
};

#endif // SUBCIRCUITVIEW_H
