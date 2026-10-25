#include "graphicsview.h"
#include "resistor.h"
#include "capacitor.h"
#include "inductor.h"
#include "voltagesource.h"
#include "currentsource.h"
#include "diode.h"
#include "zenerdiode.h"
#include <QInputDialog>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

std::shared_ptr<Node> GraphicsView::findNodeNear(const QPointF& pos, qreal radiusPx) const
{
    if (!circuitModel) return nullptr;
    const auto& nodes = circuitModel->getProjectData().nodes;
    const qreal r2 = radiusPx * radiusPx;
    for (const auto& n : nodes) {
        qreal dx = n->getX() - pos.x();
        qreal dy = n->getY() - pos.y();
        if (dx*dx + dy*dy <= r2) return n;
    }
    return nullptr;
}

void GraphicsView::promptRenameNode(const std::shared_ptr<Node>& node)
{
    if (!node) return;
    bool ok = false;
    QString current = QString::fromStdString(node->getName());
    QString name = QInputDialog::getText(this, "تغییر نام نود", "نام جدید نود:", QLineEdit::Normal, current, &ok);
    if (!ok || name.trimmed().isEmpty()) return;

    // تغییر نام نود هدف و تمام نودهای هم‌مختصات برای جلوگیری از برچسب‌های تکراری
    node->setName(name.toStdString());
    if (circuitModel) {
        auto &nodes = circuitModel->getProjectData().nodes;
        for (auto &n : nodes) {
            if (qFuzzyCompare(n->getX(), node->getX()) && qFuzzyCompare(n->getY(), node->getY())) {
                n->setName(name.toStdString());
            }
        }
    }

    updateView();
}

std::shared_ptr<Element> GraphicsView::findComponentNear(const QPointF& pos, qreal radiusPx) const
{
    if (!circuitModel) return nullptr;
    const auto& elements = circuitModel->getProjectData().elements;
    const qreal r2 = radiusPx * radiusPx;
    
    for (const auto& elem : elements) {
        if (!elem) continue;
        
        // Check if click is near the component's position (midpoint between nodes)
        if (elem->node1 && elem->node2) {
            double midX = (elem->node1->getX() + elem->node2->getX()) / 2.0;
            double midY = (elem->node1->getY() + elem->node2->getY()) / 2.0;
            
            qreal dx = midX - pos.x();
            qreal dy = midY - pos.y();
            if (dx*dx + dy*dy <= r2) return elem;
        }
    }
    return nullptr;
}

void GraphicsView::promptEditComponent(const std::shared_ptr<Element>& component)
{
    if (!component) return;
    
    QString currentName = QString::fromStdString(component->name);
    QString currentValue = getComponentValueString(component);
    
    // Create dialog for editing component properties
    QDialog dialog(this);
    dialog.setWindowTitle("ویرایش المان");
    dialog.setModal(true);
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    
    // Name field
    QHBoxLayout* nameLayout = new QHBoxLayout();
    QLabel* nameLabel = new QLabel("نام:");
    QLineEdit* nameEdit = new QLineEdit(currentName);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);
    layout->addLayout(nameLayout);
    
    // Value field
    QHBoxLayout* valueLayout = new QHBoxLayout();
    QLabel* valueLabel = new QLabel("مقدار:");
    QLineEdit* valueEdit = new QLineEdit(currentValue);
    valueLayout->addWidget(valueLabel);
    valueLayout->addWidget(valueEdit);
    layout->addLayout(valueLayout);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okButton = new QPushButton("تایید");
    QPushButton* cancelButton = new QPushButton("لغو");
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);
    
    // Connect signals
    connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    if (dialog.exec() == QDialog::Accepted) {
        QString newName = nameEdit->text().trimmed();
        QString newValue = valueEdit->text().trimmed();
        
        if (!newName.isEmpty()) {
            component->name = newName.toStdString();
        }
        
        // Update component value based on type
        if (!newValue.isEmpty()) {
            updateComponentValue(component, newValue);
        }
        
        updateView();
    }
}

QString GraphicsView::getComponentValueString(const std::shared_ptr<Element>& component) const
{
    if (!component) return "";
    
    std::string type = component->getType();
    if (type == "Resistor") {
        auto r = std::dynamic_pointer_cast<Resistor>(component);
        return r ? QString::number(r->resistance) : "";
    } else if (type == "Capacitor") {
        auto c = std::dynamic_pointer_cast<Capacitor>(component);
        return c ? QString::number(c->capacitance) : "";
    } else if (type == "Inductor") {
        auto l = std::dynamic_pointer_cast<Inductor>(component);
        return l ? QString::number(l->inductance) : "";
    } else if (type == "VoltageSource" || type == "VoltageSourceDC") {
        auto vs = std::dynamic_pointer_cast<VoltageSource>(component);
        return vs ? QString::number(vs->voltage) : "";
    } else if (type == "CurrentSource" || type == "CurrentSourceDC") {
        auto cs = std::dynamic_pointer_cast<CurrentSource>(component);
        return cs ? QString::number(cs->current) : "";
    } else if (type == "VoltageSourceSin") {
        auto vss = std::dynamic_pointer_cast<VoltageSourceSin>(component);
        return vss ? QString::number(vss->voltage) : "";
    } else if (type == "CurrentSourceSin") {
        auto css = std::dynamic_pointer_cast<CurrentSourceSin>(component);
        return css ? QString::number(css->current) : "";
    } else if (type == "Diode") {
        auto d = std::dynamic_pointer_cast<Diode>(component);
        return d ? QString::fromStdString(d->model) : "";
    } else if (type == "ZenerDiode") {
        auto zd = std::dynamic_pointer_cast<ZenerDiode>(component);
        return zd ? QString::number(zd->breakdownVoltage) : "";
    }
    
    return "";
}

void GraphicsView::updateComponentValue(const std::shared_ptr<Element>& component, const QString& newValue)
{
    if (!component) return;
    
    try {
        double value = newValue.toDouble();
        
        if (auto resistor = std::dynamic_pointer_cast<Resistor>(component)) {
            resistor->resistance = value;
        } else if (auto capacitor = std::dynamic_pointer_cast<Capacitor>(component)) {
            capacitor->capacitance = value;
        } else if (auto inductor = std::dynamic_pointer_cast<Inductor>(component)) {
            inductor->inductance = value;
        } else if (auto voltageSource = std::dynamic_pointer_cast<VoltageSource>(component)) {
            voltageSource->voltage = value;
        } else if (auto currentSource = std::dynamic_pointer_cast<CurrentSource>(component)) {
            currentSource->current = value;
        } else if (auto voltageSourceSin = std::dynamic_pointer_cast<VoltageSourceSin>(component)) {
            voltageSourceSin->voltage = value;
        } else if (auto currentSourceSin = std::dynamic_pointer_cast<CurrentSourceSin>(component)) {
            currentSourceSin->current = value;
        }
        // Add more component types as needed
    } catch (...) {
        // Value conversion failed, ignore
    }
}
