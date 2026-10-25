// =======================================================================
// =======================================================================
//
//   FILE: src/View/mainwindow.h (Updated)
//
// =======================================================================
// =======================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPalette>
#include "applicationcontroller.h"
#include "plotter.h"
#include "networkmanager.h"
#include "graphicsview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
        void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAsSubcircuit_triggered();
    void on_actionAddComponent_triggered();
    void on_actionRunAnalysis_triggered();
    void on_actionStartServer_triggered();
    void on_actionSendData_triggered();
    void on_actionToggleTheme_triggered();
    void onAnalysisCompleted(const QString& resultFilePath);
    void updateStatusBar(const QString& message);
    void onProjectLoaded();
    void onNetworkDataReceived(const QByteArray& data);
    void updateLibrary();
    void onLibraryComponentTriggered();
    void on_actionAddMathTrace_triggered();
    
    // نمودارهای پیش‌فرض
    void showDefaultCharts();
    void on_actionChangeChartColors_triggered();
    void on_actionRenameSignal_triggered();
    
    // اسکیل جداگانه محورها
    void on_actionScaleXAxisIn_triggered();
    void on_actionScaleXAxisOut_triggered();
    void on_actionScaleYLeftAxisIn_triggered();
    void on_actionScaleYLeftAxisOut_triggered();
    void on_actionScaleYRightAxisIn_triggered();
    void on_actionScaleYRightAxisOut_triggered();
    
    // دابل کرسر
    void on_actionEnableDoubleCursor_triggered();
    void on_actionDisableDoubleCursor_triggered();
    
    // پروب
    void on_actionVoltageProbe_triggered();
    void on_actionCurrentProbe_triggered();
    void on_actionPowerProbe_triggered();
    void on_actionDisableProbe_triggered();
    
    // Subcircuit management
    void on_actionCreateSubcircuit_triggered();
    void on_actionSelectSubcircuitPins_triggered();
    void on_actionSaveSubcircuit_triggered();
    
    // Access to GraphicsView for subcircuit data
    GraphicsView* getSchematicView() const { return schematicView; }
    
    // Keyboard shortcuts for component selection
    void on_actionResistor_triggered();
    void on_actionCapacitor_triggered();
    void on_actionInductor_triggered();
    void on_actionVoltageSource_triggered();
    void on_actionCurrentSource_triggered();
    void on_actionDiode_triggered();
    void on_actionZenerDiode_triggered();
    void on_actionWire_triggered();

private:
    void createMenus();
    void createToolBars();
    void applyTheme();

    Ui::MainWindow *ui;
    ApplicationController controller;
    Plotter* plotter;
    NetworkManager networkManager;
    QMenu* libraryMenu;
    GraphicsView* schematicView;

    bool isDarkMode = false;
};
#endif // MAINWINDOW_H