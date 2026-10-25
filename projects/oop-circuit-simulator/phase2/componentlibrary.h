#ifndef COMPONENTLIBRARY_H
#define COMPONENTLIBRARY_H

#include <QDockWidget>
#include "circuitcomponent.h" // Provides the ComponentType enum

class QToolBox;

class ComponentLibrary : public QDockWidget {
Q_OBJECT

public:
    explicit ComponentLibrary(const QString &title, QWidget *parent = nullptr);

    // This function must be declared here
    void refreshSubcircuits();

signals:
    // This signal signature is critical and must have both arguments
    void componentSelected(ComponentType type, const QString& subcircuitFile);

private:
    void populateBasicComponents();
    void populateSubcircuits();

    QToolBox *toolBox;
    QWidget *basicComponentsWidget;
    QWidget *subcircuitsWidget;
};

#endif // COMPONENTLIBRARY_H