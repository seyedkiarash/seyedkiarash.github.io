#include "componentlibrary.h"
#include <QListWidget>
#include <QListWidgetItem> // ADDED: Header for QListWidgetItem
#include <QSet>            // ADDED: Header for QSet

ComponentLibrary::ComponentLibrary(const QString &title, QWidget *parent)
        : QDockWidget(title, parent) {
    listWidget = new QListWidget(this);
    setWidget(listWidget);

    // Populate with standard components
    listWidget->addItem("Resistor");
    listWidget->addItem("Capacitor");
    listWidget->addItem("Inductor");
    listWidget->addItem("Voltage Source");
    listWidget->addItem("Wire");
    listWidget->addItem("Node Label");
    listWidget->addItem("Waveform Source");

    connect(listWidget, &QListWidget::itemDoubleClicked, this, &ComponentLibrary::onComponentDoubleClicked);
}

void ComponentLibrary::addSubcircuit(const QString &name) {
    listWidget->addItem(name);
}

void ComponentLibrary::clearSubcircuits() {
    QSet<QString> standardComponents = {
            "Resistor", "Capacitor", "Inductor", "Voltage Source",
            "Wire", "Node Label", "Waveform Source"
    };

    for (int i = listWidget->count() - 1; i >= 0; --i) {
        if (!standardComponents.contains(listWidget->item(i)->text())) {
            delete listWidget->takeItem(i);
        }
    }
}

void ComponentLibrary::onComponentDoubleClicked(QListWidgetItem *item) {
    QString text = item->text();
    ComponentType type = ComponentType::None;
    QString subcircuitFile = "";

    if (text == "Resistor") type = ComponentType::Resistor;
    else if (text == "Capacitor") type = ComponentType::Capacitor;
    else if (text == "Inductor") type = ComponentType::Inductor;
    else if (text == "Voltage Source") type = ComponentType::VoltageSource;
    else if (text == "Wire") type = ComponentType::Wire;
    else if (text == "Node Label") type = ComponentType::NodeLabel;
    else if (text == "Waveform Source") type = ComponentType::WaveformSource;
    else {
        // If it's not a standard component, it must be a subcircuit
        type = ComponentType::Subcircuit;
        subcircuitFile = "lib/" + text + ".sub";
    }

    if (type != ComponentType::None) {
        emit componentSelected(type, subcircuitFile);
    }
}