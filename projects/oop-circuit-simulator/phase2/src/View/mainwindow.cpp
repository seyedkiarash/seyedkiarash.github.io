// =======================================================================
// =======================================================================
//
//   FILE: src/View/mainwindow.cpp (Updated)
//
// =======================================================================
// =======================================================================

#include "mainwindow.h"
#include "simulationdialog.h"
#include "componentdialog.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QIcon>
#include <sstream>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenus();
    createToolBars();
    plotter = new Plotter(this);

    QToolButton *zoomInButton = new QToolButton();
    zoomInButton->setIcon(QIcon::fromTheme("zoom-in"));
    zoomInButton->setToolTip("بزرگ‌نمایی");
    QToolButton *zoomOutButton = new QToolButton();
    zoomOutButton->setIcon(QIcon::fromTheme("zoom-out"));
    zoomOutButton->setToolTip("کوچک‌نمایی");
    QToolButton *resetZoomButton = new QToolButton();
    resetZoomButton->setIcon(QIcon::fromTheme("zoom-original"));
    resetZoomButton->setToolTip("بازنشانی نما");
    QToolButton *autoZoomButton = new QToolButton();
    autoZoomButton->setIcon(QIcon::fromTheme("zoom-fit-best"));
    autoZoomButton->setToolTip("زوم خودکار (Auto Zoom)");
    QToolButton *addTraceButton = new QToolButton();
    addTraceButton->setIcon(QIcon::fromTheme("list-add"));
    addTraceButton->setToolTip("اضافه کردن سیگنال محاسباتی");

    connect(zoomInButton, &QToolButton::clicked, plotter, &Plotter::zoomIn);
    connect(zoomOutButton, &QToolButton::clicked, plotter, &Plotter::zoomOut);
    connect(resetZoomButton, &QToolButton::clicked, plotter, &Plotter::resetZoom);
    connect(autoZoomButton, &QToolButton::clicked, plotter, &Plotter::autoZoom);
    connect(plotter, &Plotter::updateStatusBar, this, &MainWindow::updateStatusBar);
    connect(addTraceButton, &QToolButton::clicked, this, &MainWindow::on_actionAddMathTrace_triggered);

    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(zoomInButton);
    controlsLayout->addWidget(zoomOutButton);
    controlsLayout->addWidget(resetZoomButton);
    controlsLayout->addWidget(autoZoomButton);
    controlsLayout->addWidget(addTraceButton);
    controlsLayout->addStretch();

    QVBoxLayout *plotterLayout = new QVBoxLayout();
    plotterLayout->addLayout(controlsLayout);
    plotterLayout->addWidget(plotter);
    QWidget *plotterContainer = new QWidget();
    plotterContainer->setLayout(plotterLayout);
    QDockWidget *plotterDock = new QDockWidget("نمایشگر نمودار", this);
    plotterDock->setWidget(plotterContainer);
    addDockWidget(Qt::BottomDockWidgetArea, plotterDock);

    schematicView = new GraphicsView(this);
    CircuitModel* model = controller.getModel();
    qDebug() << "MainWindow constructor: model pointer:" << model;
    schematicView->setCircuitModel(model);
    setCentralWidget(schematicView);

    connect(&controller, &ApplicationController::analysisCompleted, this, &MainWindow::onAnalysisCompleted);
    connect(&controller, &ApplicationController::statusMessageChanged, this, &MainWindow::updateStatusBar);
    connect(&controller, &ApplicationController::projectLoaded, this, &MainWindow::onProjectLoaded);
    connect(&networkManager, &NetworkManager::logMessage, this, &MainWindow::updateStatusBar);
    connect(&networkManager, &NetworkManager::dataReceived, this, &MainWindow::onNetworkDataReceived);
    connect(&controller, &ApplicationController::libraryChanged, this, &MainWindow::updateLibrary);

    statusBar()->showMessage("آماده.");
    setWindowTitle("Kia-Farzin Circuit Simulator");
    resize(1200, 800);
    applyTheme();
    controller.scanForSubcircuits();
    controller.createNewProject();
}

MainWindow::~MainWindow() {}

 void MainWindow::on_actionAddMathTrace_triggered() {
    QStringList signalNames = plotter->getSignalNames();
    if (signalNames.count() < 2) {
        QMessageBox::warning(this, "خطا", "برای انجام عملیات ریاضی حداقل به دو سیگنال نیاز است.");
        return;
    }
    bool ok = false;
    QString a = QInputDialog::getItem(this, "انتخاب سیگنال اول", "سیگنال A:", signalNames, 0, false, &ok);
    if (!ok) return;
    QString b = QInputDialog::getItem(this, "انتخاب سیگنال دوم", "سیگنال B:", signalNames, 1, false, &ok);
    if (!ok) return;
    QStringList ops = {"+","-","*","/"};
    QString op = QInputDialog::getItem(this, "انتخاب عملگر", "عملگر:", ops, 0, false, &ok);
    if (!ok) return;
    QString resName = QInputDialog::getText(this, "نام نتیجه", "نام سیگنال نتیجه:", QLineEdit::Normal, a + op + b, &ok);
    if (!ok || resName.isEmpty()) return;
    plotter->addMathTrace(a, b, op, resName);
 }

void MainWindow::onProjectLoaded() {
    plotter->clearChart();
    schematicView->updateView();
    updateStatusBar("پروژه بارگذاری شد.");
}

// ... (بقیه کدهای mainwindow.cpp بدون تغییر) ...
void MainWindow::createToolBars() {
    QToolBar *probeToolBar = addToolBar("Probes");
    const QIcon voltageProbeIcon = QIcon::fromTheme("input-mouse");
    QAction *voltageProbeAct = new QAction(voltageProbeIcon, "پراب ولتاژ", this);
    connect(voltageProbeAct, &QAction::triggered, this, &MainWindow::on_actionVoltageProbe_triggered);
    probeToolBar->addAction(voltageProbeAct);
    const QIcon currentProbeIcon = QIcon::fromTheme("input-tablet");
    QAction *currentProbeAct = new QAction(currentProbeIcon, "پراب جریان", this);
    connect(currentProbeAct, &QAction::triggered, this, &MainWindow::on_actionCurrentProbe_triggered);
    probeToolBar->addAction(currentProbeAct);
}
void MainWindow::on_actionVoltageProbe_triggered() {
    schematicView->setProbeMode(1);
    updateStatusBar("پروب ولتاژ فعال شد.");
}
void MainWindow::on_actionCurrentProbe_triggered() {
    schematicView->setProbeMode(2);
    updateStatusBar("پروب جریان فعال شد.");
}
void MainWindow::createMenus() {
    QMenu *fileMenu = menuBar()->addMenu("فایل");
    fileMenu->addAction("جدید", this, &MainWindow::on_actionNew_triggered);
    fileMenu->addAction("باز کردن...", this, &MainWindow::on_actionOpen_triggered);
    fileMenu->addAction("ذخیره...", this, &MainWindow::on_actionSave_triggered);
    fileMenu->addAction("ذخیره به عنوان تک‌قطبی...", this, &MainWindow::on_actionSaveAsSubcircuit_triggered);
    
    QMenu *editMenu = menuBar()->addMenu("ویرایش");
    editMenu->addAction("اضافه کردن المان...", this, &MainWindow::on_actionAddComponent_triggered);
    
    // Quick component actions with keyboard shortcuts
    QAction *resistorAction = editMenu->addAction("مقاومت (Ctrl+R)", this, &MainWindow::on_actionResistor_triggered);
    resistorAction->setShortcut(QKeySequence("Ctrl+R"));
    QAction *capacitorAction = editMenu->addAction("خازن (Ctrl+C)", this, &MainWindow::on_actionCapacitor_triggered);
    capacitorAction->setShortcut(QKeySequence("Ctrl+C"));
    QAction *inductorAction = editMenu->addAction("سلف (Ctrl+L)", this, &MainWindow::on_actionInductor_triggered);
    inductorAction->setShortcut(QKeySequence("Ctrl+L"));
    QAction *voltageAction = editMenu->addAction("منبع ولتاژ DC (Ctrl+V)", this, &MainWindow::on_actionVoltageSource_triggered);
    voltageAction->setShortcut(QKeySequence("Ctrl+V"));
    QAction *currentAction = editMenu->addAction("منبع جریان DC (Ctrl+I)", this, &MainWindow::on_actionCurrentSource_triggered);
    currentAction->setShortcut(QKeySequence("Ctrl+I"));
    QAction *diodeAction = editMenu->addAction("دیود (Ctrl+D)", this, &MainWindow::on_actionDiode_triggered);
    diodeAction->setShortcut(QKeySequence("Ctrl+D"));
    QAction *zenerAction = editMenu->addAction("دیود زنر (Ctrl+Z)", this, &MainWindow::on_actionZenerDiode_triggered);
    zenerAction->setShortcut(QKeySequence("Ctrl+Z"));
    
    editMenu->addSeparator();
    QAction *wireAction = editMenu->addAction("سیم کشی (Ctrl+W)", this, &MainWindow::on_actionWire_triggered);
    wireAction->setShortcut(QKeySequence("Ctrl+W"));
    
    // Subcircuit menu
    QMenu *subcircuitMenu = menuBar()->addMenu("تک‌قطبی");
    subcircuitMenu->addAction("ایجاد تک‌قطبی جدید", this, &MainWindow::on_actionCreateSubcircuit_triggered);
    subcircuitMenu->addAction("انتخاب پین‌های تک‌قطبی", this, &MainWindow::on_actionSelectSubcircuitPins_triggered);
    subcircuitMenu->addAction("ذخیره تک‌قطبی", this, &MainWindow::on_actionSaveSubcircuit_triggered);
    
    libraryMenu = menuBar()->addMenu("کتابخانه");
    QMenu *simMenu = menuBar()->addMenu("شبیه‌سازی");
    simMenu->addAction("تنظیمات و اجرا...", this, &MainWindow::on_actionRunAnalysis_triggered);
    QMenu* networkMenu = menuBar()->addMenu("شبکه");
    networkMenu->addAction("راه اندازی سرور", this, &MainWindow::on_actionStartServer_triggered);
    networkMenu->addAction("ارسال داده", this, &MainWindow::on_actionSendData_triggered);
    QMenu* settingsMenu = menuBar()->addMenu("تنظیمات");
    settingsMenu->addAction("تغییر تم", this, &MainWindow::on_actionToggleTheme_triggered);
    
    // منوی نمودار
    QMenu* chartMenu = menuBar()->addMenu("نمودار");
    chartMenu->addAction("نمایش نمودارهای پیش‌فرض", this, &MainWindow::showDefaultCharts);
    chartMenu->addAction("تغییر رنگ نمودارها", this, &MainWindow::on_actionChangeChartColors_triggered);
    
    // زیرمنوی زوم
    QMenu* zoomMenu = chartMenu->addMenu("زوم");
    zoomMenu->addAction("زوم این", this, [this]() { plotter->zoomIn(); });
    zoomMenu->addAction("زوم اوت", this, [this]() { plotter->zoomOut(); });
    zoomMenu->addAction("ریست زوم", this, [this]() { plotter->resetZoom(); });
    
    // زیرمنوی اسکیل محورها
    QMenu* scaleMenu = chartMenu->addMenu("اسکیل محورها");
    
    // اسکیل محور X (زمان)
    QMenu* xScaleMenu = scaleMenu->addMenu("محور X (زمان)");
    xScaleMenu->addAction("اسکیل این", this, &MainWindow::on_actionScaleXAxisIn_triggered);
    xScaleMenu->addAction("اسکیل اوت", this, &MainWindow::on_actionScaleXAxisOut_triggered);
    
    // اسکیل محور Y چپ (ولتاژ)
    QMenu* yLeftScaleMenu = scaleMenu->addMenu("محور Y چپ (ولتاژ)");
    yLeftScaleMenu->addAction("اسکیل این", this, &MainWindow::on_actionScaleYLeftAxisIn_triggered);
    yLeftScaleMenu->addAction("اسکیل اوت", this, &MainWindow::on_actionScaleYLeftAxisOut_triggered);
    
    // اسکیل محور Y راست (جریان)
    QMenu* yRightScaleMenu = scaleMenu->addMenu("محور Y راست (جریان)");
    yRightScaleMenu->addAction("اسکیل این", this, &MainWindow::on_actionScaleYRightAxisIn_triggered);
    yRightScaleMenu->addAction("اسکیل اوت", this, &MainWindow::on_actionScaleYRightAxisOut_triggered);
    
    // زیرمنوی دابل کرسر
    QMenu* cursorMenu = chartMenu->addMenu("دابل کرسر");
    cursorMenu->addAction("فعال کردن دابل کرسر", this, &MainWindow::on_actionEnableDoubleCursor_triggered);
    cursorMenu->addAction("غیرفعال کردن دابل کرسر", this, &MainWindow::on_actionDisableDoubleCursor_triggered);
    
    // زیرمنوی پروب
    QMenu* probeMenu = chartMenu->addMenu("پروب");
    probeMenu->addAction("پروب ولتاژ", this, &MainWindow::on_actionVoltageProbe_triggered);
    probeMenu->addAction("پروب جریان", this, &MainWindow::on_actionCurrentProbe_triggered);
    probeMenu->addAction("پروب توان", this, &MainWindow::on_actionPowerProbe_triggered);
    probeMenu->addSeparator();
    probeMenu->addAction("غیرفعال کردن پروب", this, &MainWindow::on_actionDisableProbe_triggered);
    
    // تغییر نام سیگنال
    chartMenu->addAction("تغییر نام سیگنال", this, &MainWindow::on_actionRenameSignal_triggered);
}
void MainWindow::updateLibrary() {
    libraryMenu->clear();
    QStringList subcircuits = controller.getAvailableSubcircuits();
    if (subcircuits.isEmpty()) {
        libraryMenu->addAction("کتابخانه خالی است")->setEnabled(false);
    } else {
        for (const QString &name : subcircuits) {
            QAction *action = libraryMenu->addAction(name);
            connect(action, &QAction::triggered, this, &MainWindow::onLibraryComponentTriggered);
        }
    }
}
void MainWindow::onLibraryComponentTriggered() {
    QAction *action = qobject_cast<QAction*>(sender());
    if (action) {
        QString componentName = action->text();
        controller.addSubcircuitToProject(componentName);
        updateStatusBar("تک‌قطبی " + componentName + " انتخاب شد. حالا روی شماتیک کلیک کنید تا قرار گیرد.");
        
        // Enable placement mode for the subcircuit
        schematicView->startPlacing("SubCircuit");
        schematicView->setCursor(Qt::CrossCursor);
    }
}
void MainWindow::on_actionSaveAsSubcircuit_triggered() {
    bool ok;
    QString name = QInputDialog::getText(this, "ذخیره به عنوان تک‌قطبی", "نام تک‌قطبی:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        controller.saveAsSubcircuit(name);
    }
}
void MainWindow::on_actionAddComponent_triggered() {
    ComponentDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString componentName = dialog.getSelectedComponent();
        if (!componentName.isEmpty()) {
            // تشخیص نوع منطقی از متن دیالوگ
            QString type = componentName;
            if (componentName.startsWith("SubCircuit:")) {
                // در آینده: بارگذاری تک‌قطبی انتخاب‌شده
                updateStatusBar("تک‌قطبی انتخاب شد، فعلا پشتیبانی قراردهی مستقیم ندارد.");
                return;
            } else {
                type = componentName.split(" ").first(); // Resistor/Capacitor/...
            }
            updateStatusBar("آماده برای قرار دادن " + type + ". با کلیک چپ قرار دهید، راست برای لغو.");
            schematicView->startPlacing(type);
            schematicView->setCursor(Qt::CrossCursor);
        }
    }
}
void MainWindow::on_actionRunAnalysis_triggered() {
    // قطع ارتباط با موتور تحلیل - نمایش نمودارهای پیش‌فرض
    showDefaultCharts();
}
void MainWindow::on_actionToggleTheme_triggered() {
    isDarkMode = !isDarkMode;
    applyTheme();
}
void MainWindow::applyTheme() {
    if (isDarkMode) {
        QString darkStyleSheet = R"(
            QWidget { background-color: #353535; color: #FFFFFF; border: 0px; }
            QMainWindow, QMenuBar, QMenu { background-color: #2E2E2E; color: #FFFFFF; }
            QMenuBar::item:selected { background-color: #555555; }
            QMenu::item:selected { background-color: #0078D7; color: #FFFFFF; }
            QStatusBar { background-color: #2E2E2E; }
            QDockWidget::title { background-color: #454545; padding: 4px; }
            QTextEdit, QLineEdit, QComboBox, QListWidget { background-color: #252525; border: 1px solid #555555; }
            QListWidget::item:selected { background-color: #0078D7; }
            QPushButton, QToolButton { background-color: #555555; padding: 5px; border-radius: 3px; }
            QPushButton:hover, QToolButton:hover { background-color: #666666; }
            QDialogButtonBox QPushButton { min-width: 80px; }
        )";
        qApp->setStyleSheet(darkStyleSheet);
        plotter->setDarkTheme();
    } else {
        qApp->setStyleSheet("");
        plotter->setLightTheme();
    }
}
void MainWindow::on_actionNew_triggered() { controller.createNewProject(); }
void MainWindow::on_actionOpen_triggered() {
    QString filePath = QFileDialog::getOpenFileName(this, "باز کردن پروژه", "", "فایل پروژه (*.proj)");
    if (!filePath.isEmpty()) controller.loadProject(filePath);
}
void MainWindow::on_actionSave_triggered() {
    QString filePath = QFileDialog::getSaveFileName(this, "ذخیره پروژه", "", "فایل پروژه (*.proj)");
    if (!filePath.isEmpty()) controller.saveProject(filePath);
}
void MainWindow::on_actionStartServer_triggered() {
    bool ok;
    int port = QInputDialog::getInt(this, "راه اندازی سرور", "پورت:", 1234, 1024, 65535, 1, &ok);
    if (ok) networkManager.startServer(port);
}
void MainWindow::on_actionSendData_triggered() {
    if(controller.getModel()->getProjectData().elements.empty()){
        updateStatusBar("خطا: هیچ المانی برای ارسال وجود ندارد.");
        return;
    }
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive archive(ss);
        archive(controller.getModel()->getProjectData().elements.front());
    }
    std::string data_str = ss.str();
    QByteArray data(data_str.c_str(), data_str.length());
    QString ip = QInputDialog::getText(this, "ارسال داده", "آدرس IP سرور:");
    int port = QInputDialog::getInt(this, "ارسال داده", "پورت سرور:");
    if(!ip.isEmpty()) networkManager.sendData(data, ip, port);
}
void MainWindow::onAnalysisCompleted(const QString& resultFilePath) { plotter->loadDataFromFile(resultFilePath); }

void MainWindow::showDefaultCharts() {
    // قطع ارتباط با موتور تحلیل و نمایش نمودارهای پیش‌فرض
    plotter->clearChart();
    
    // ایجاد 3 نمودار پیش‌فرض شبیه LTSPICE
    plotter->addDefaultSineWave("V(n002)", QColor(0, 0, 255));      // آبی - ولتاژ
    plotter->addDefaultDCWave("I(R8)", QColor(0, 255, 0));          // سبز - جریان
    plotter->addDefaultCosineWave("V(n003)", QColor(255, 0, 0));    // قرمز - ولتاژ
    
    updateStatusBar("نمودارهای پیش‌فرض شبیه LTSPICE نمایش داده شدند.");
}

void MainWindow::on_actionChangeChartColors_triggered() {
    // تغییر رنگ نمودارها
    plotter->changeChartColors();
    updateStatusBar("رنگ نمودارها تغییر کرد.");
}

void MainWindow::on_actionRenameSignal_triggered() {
    plotter->showRenameSignalDialog();
}

// =======================================================================
// اسکیل جداگانه محورها
// =======================================================================

void MainWindow::on_actionScaleXAxisIn_triggered() {
    plotter->scaleXAxis(1.2);
    updateStatusBar("اسکیل محور X (زمان) افزایش یافت.");
}

void MainWindow::on_actionScaleXAxisOut_triggered() {
    plotter->scaleXAxis(1.0 / 1.2);
    updateStatusBar("اسکیل محور X (زمان) کاهش یافت.");
}

void MainWindow::on_actionScaleYLeftAxisIn_triggered() {
    plotter->scaleYLeftAxis(1.2);
    updateStatusBar("اسکیل محور Y چپ (ولتاژ) افزایش یافت.");
}

void MainWindow::on_actionScaleYLeftAxisOut_triggered() {
    plotter->scaleYLeftAxis(1.0 / 1.2);
    updateStatusBar("اسکیل محور Y چپ (ولتاژ) کاهش یافت.");
}

void MainWindow::on_actionScaleYRightAxisIn_triggered() {
    plotter->scaleYRightAxis(1.2);
    updateStatusBar("اسکیل محور Y راست (جریان) افزایش یافت.");
}

void MainWindow::on_actionScaleYRightAxisOut_triggered() {
    plotter->scaleYRightAxis(1.0 / 1.2);
    updateStatusBar("اسکیل محور Y راست (جریان) کاهش یافت.");
}

// =======================================================================
// دابل کرسر
// =======================================================================

void MainWindow::on_actionEnableDoubleCursor_triggered() {
    plotter->enableDoubleCursor();
    updateStatusBar("حالت دابل کرسر فعال شد.");
}

void MainWindow::on_actionDisableDoubleCursor_triggered() {
    plotter->disableDoubleCursor();
    updateStatusBar("حالت دابل کرسر غیرفعال شد.");
}

// =======================================================================
// پروب
// =======================================================================

void MainWindow::on_actionPowerProbe_triggered() {
    schematicView->setProbeMode(3);
    updateStatusBar("پروب توان فعال شد.");
}

void MainWindow::on_actionDisableProbe_triggered() {
    schematicView->setProbeMode(0);
    updateStatusBar("پروب غیرفعال شد.");
}
void MainWindow::updateStatusBar(const QString& message) { statusBar()->showMessage(message); }

void MainWindow::onNetworkDataReceived(const QByteArray& data) {
    try {
        std::stringstream ss;
        ss.write(data.constData(), data.size());
        cereal::BinaryInputArchive archive(ss);
        std::shared_ptr<Element> receivedElement;
        archive(receivedElement);
        
        // اضافه کردن المان به پروژه
        controller.getModel()->getProjectData().elements.push_back(receivedElement);
        qDebug() << "Element added to project. Total elements:" << controller.getModel()->getProjectData().elements.size();
        
        // ایجاد نودهای المان در صورت نیاز
        if (receivedElement->node1) {
            controller.getModel()->getProjectData().nodes.push_back(receivedElement->node1);
            qDebug() << "Node1 added:" << receivedElement->node1->getX() << "," << receivedElement->node1->getY();
        }
        if (receivedElement->node2) {
            controller.getModel()->getProjectData().nodes.push_back(receivedElement->node2);
            qDebug() << "Node2 added:" << receivedElement->node2->getX() << "," << receivedElement->node2->getY();
        }
        
        // به‌روزرسانی شماتیک
        qDebug() << "Updating schematic view...";
        schematicView->updateView();
        qDebug() << "Schematic view updated.";
        
        QMessageBox::information(this, "داده شبکه دریافت شد", "یک المان از نوع " + QString::fromStdString(receivedElement->getType()) + " دریافت شد و به شماتیک اضافه شد.");
        updateStatusBar("المان " + QString::fromStdString(receivedElement->getType()) + " از شبکه دریافت شد.");
        
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "خطا", "خطا در پردازش داده شبکه: " + QString(e.what()));
        qDebug() << "Network data processing error:" << e.what();
    } catch (...) {
        QMessageBox::warning(this, "خطا", "خطای نامشخص در پردازش داده شبکه.");
        qDebug() << "Unknown network data processing error";
    }
}

// Keyboard shortcut handlers for quick component selection
void MainWindow::on_actionResistor_triggered() {
    updateStatusBar("آماده برای قرار دادن مقاومت. با کلیک چپ قرار دهید، راست برای لغو.");
    schematicView->startPlacing("Resistor");
    schematicView->setCursor(Qt::CrossCursor);
}

void MainWindow::on_actionCapacitor_triggered() {
    updateStatusBar("آماده برای قرار دادن خازن. با کلیک چپ قرار دهید، راست برای لغو.");
    schematicView->startPlacing("Capacitor");
    schematicView->setCursor(Qt::CrossCursor);
}

void MainWindow::on_actionInductor_triggered() {
    updateStatusBar("آماده برای قرار دادن سلف. با کلیک چپ قرار دهید، راست برای لغو.");
    schematicView->startPlacing("Inductor");
    schematicView->setCursor(Qt::CrossCursor);
}

void MainWindow::on_actionVoltageSource_triggered() {
    updateStatusBar("آماده برای قرار دادن منبع ولتاژ DC. با کلیک چپ قرار دهید، راست برای لغو.");
    schematicView->startPlacing("VoltageSourceDC");
    schematicView->setCursor(Qt::CrossCursor);
}

void MainWindow::on_actionCurrentSource_triggered() {
    updateStatusBar("آماده برای قرار دادن منبع جریان DC. با کلیک چپ قرار دهید، راست برای لغو.");
    schematicView->startPlacing("CurrentSourceDC");
    schematicView->setCursor(Qt::CrossCursor);
}

void MainWindow::on_actionDiode_triggered() {
    updateStatusBar("آماده برای قرار دادن دیود. با کلیک چپ قرار دهید، راست برای لغو.");
    schematicView->startPlacing("Diode");
    schematicView->setCursor(Qt::CrossCursor);
}

void MainWindow::on_actionZenerDiode_triggered() {
    updateStatusBar("آماده برای قرار دادن دیود زنر. با کلیک چپ قرار دهید، راست برای لغو.");
    schematicView->startPlacing("ZenerDiode");
    schematicView->setCursor(Qt::CrossCursor);
}

void MainWindow::on_actionWire_triggered() {
    updateStatusBar("حالت سیم کشی فعال شد. کلیک چپ برای شروع/اضافه کردن نقاط، کلیک راست برای پایان.");
    schematicView->startWireDrawing();
}

// Subcircuit management functions
void MainWindow::on_actionCreateSubcircuit_triggered() {
    updateStatusBar("حالت ایجاد تک‌قطبی فعال شد. ابتدا المان‌ها را قرار دهید، سپس پین‌ها را انتخاب کنید.");
    // Enable subcircuit creation mode
    schematicView->setSubcircuitCreationMode(true);
}

void MainWindow::on_actionSelectSubcircuitPins_triggered() {
    updateStatusBar("انتخاب پین‌های تک‌قطبی. روی دو گره کلیک کنید تا به عنوان پین انتخاب شوند.");
    schematicView->setPinSelectionMode(true);
}

void MainWindow::on_actionSaveSubcircuit_triggered() {
    QString name = QInputDialog::getText(this, "ذخیره تک‌قطبی", "نام تک‌قطبی:");
    if (!name.isEmpty()) {
        // Check if we have selected pins
        if (schematicView->isPinSelectionMode() || schematicView->getSelectedPins().size() == 2) {
            // Use selected pins
            auto pins = schematicView->getSelectedPins();
            if (pins.size() == 2) {
                if (controller.saveAsSubcircuitWithPins(name, pins)) {
                    updateStatusBar("تک‌قطبی " + name + " با پین‌های انتخاب شده ذخیره شد.");
                } else {
                    QMessageBox::warning(this, "خطا", "خطا در ذخیره تک‌قطبی با پین‌های انتخاب شده.");
                }
            } else {
                QMessageBox::warning(this, "خطا", "لطفاً ابتدا دو پین را انتخاب کنید.");
            }
        } else {
            // Use default pins (first two nodes)
            if (controller.saveAsSubcircuit(name)) {
                updateStatusBar("تک‌قطبی " + name + " با موفقیت ذخیره شد.");
            } else {
                QMessageBox::warning(this, "خطا", "خطا در ذخیره تک‌قطبی.");
            }
        }
    }
}
