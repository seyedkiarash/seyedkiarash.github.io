// =======================================================================
// =======================================================================
//
//   FILE: src/View/circuitcomponent.h (New File)
//
// =======================================================================
// =======================================================================

#ifndef CIRCUITCOMPONENT_H
#define CIRCUITCOMPONENT_H

#include <QGraphicsObject>
#include <QList>
#include <QPointF>
#include "datatypes.h" // برای دسترسی به مدل منطقی

// این کلاس پایه برای تمام المان‌های گرافیکی در صحنه است
class CircuitComponent : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CircuitComponent(std::shared_ptr<Element> elementLogic, QGraphicsItem *parent = nullptr);
    virtual ~CircuitComponent() = default;

    // متد برای به‌روزرسانی موقعیت بر اساس مدل منطقی
    void updateFromLogic();
    std::shared_ptr<Element> getLogicElement() const;

protected:
    // اشاره‌گر به المان منطقی متناظر در Model
    std::shared_ptr<Element> logicElement;
};

#endif // CIRCUITCOMPONENT_H

