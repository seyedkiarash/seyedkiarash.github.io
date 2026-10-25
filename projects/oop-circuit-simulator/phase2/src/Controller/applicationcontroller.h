// =======================================================================
// FILE: applicationcontroller.h
//========================================================================
#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>
#include <QStringList>
#include "circuitmodel.h"
#include <string>

class ApplicationController : public QObject {
    Q_OBJECT

public:
    explicit ApplicationController(QObject *parent = nullptr);

    // متدهای فراخوانی شده توسط View
    void runAnalysis(const SimulationSettings& settings);
    void saveProject(const QString& filePath);
    void loadProject(const QString& filePath);
    void createNewProject();
    CircuitModel* getModel();

    // --- متدهای جدید برای مدیریت تک‌قطبی‌ها ---
    void scanForSubcircuits();
    QStringList getAvailableSubcircuits() const;
    void addSubcircuitToProject(const QString& name);
    bool saveAsSubcircuit(const QString& name);
    bool saveAsSubcircuitWithPins(const QString& name, const std::vector<std::shared_ptr<Node>>& pins);

    signals:
        // سیگنال‌هایی که به View ارسال می‌شوند
        void analysisCompleted(const QString& resultFilePath);
    void projectLoaded();
    void statusMessageChanged(const QString& message);
    void libraryChanged(); // <-- سیگنال جدید برای اطلاع‌رسانی به View

private:
    CircuitModel model;
    QStringList availableSubcircuits;
};

#endif // APPLICATIONCONTROLLER_H
