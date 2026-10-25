// =======================================================================
// FILE: simulationdialog.cpp
// =======================================================================
// پیاده‌سازی دیالوگ تنظیمات شبیه‌سازی.
//========================================================================
#include "simulationdialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>

SimulationDialog::SimulationDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("تنظیمات شبیه‌سازی");
    setMinimumWidth(400);

    tabWidget = new QTabWidget(this);

    // --- تب تحلیل گذرا (Transient) ---
    QWidget *transientTab = new QWidget;
    QFormLayout *transientLayout = new QFormLayout(transientTab);
    stopTimeEdit = new QLineEdit("1m");
    startTimeEdit = new QLineEdit("0"); // <-- ایجاد ویجت جدید
    timeStepEdit = new QLineEdit("1u");
    transientLayout->addRow("زمان توقف (Stop Time):", stopTimeEdit);
    transientLayout->addRow("زمان شروع ذخیره (Time to start saving data):", startTimeEdit); // <-- اضافه کردن به لایوت
    transientLayout->addRow("گام زمانی (Maximum Timestep):", timeStepEdit);
    tabWidget->addTab(transientTab, "Transient");

    // --- تب تحلیل فرکانسی (AC Sweep) ---
    QWidget *acTab = new QWidget;
    QFormLayout *acLayout = new QFormLayout(acTab);
    sweepTypeCombo = new QComboBox;
    sweepTypeCombo->addItems({"Linear", "Octave", "Decade"});
    startFreqEdit = new QLineEdit("1");
    stopFreqEdit = new QLineEdit("1M");
    pointsEditAC = new QLineEdit("100");
    acLayout->addRow("نوع Sweep:", sweepTypeCombo);
    acLayout->addRow("فرکانس شروع (Start Frequency):", startFreqEdit);
    acLayout->addRow("فرکانس توقف (Stop Frequency):", stopFreqEdit);
    acLayout->addRow("تعداد نقاط (Number of Points):", pointsEditAC);
    tabWidget->addTab(acTab, "AC Sweep");

    // --- تب تحلیل فاز (Phase Sweep) ---
    QWidget *phaseTab = new QWidget;
    QFormLayout *phaseLayout = new QFormLayout(phaseTab);
    baseFreqEdit = new QLineEdit("1k");
    startPhaseEdit = new QLineEdit("0");
    stopPhaseEdit = new QLineEdit("360");
    pointsEditPhase = new QLineEdit("100");
    phaseLayout->addRow("فرکانس پایه (Base Frequency):", baseFreqEdit);
    phaseLayout->addRow("فاز شروع (Start Phase):", startPhaseEdit);
    phaseLayout->addRow("فاز توقف (Stop Phase):", stopPhaseEdit);
    phaseLayout->addRow("تعداد نقاط (Number of Points):", pointsEditPhase);
    tabWidget->addTab(phaseTab, "Phase Sweep");

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
}

SimulationSettings SimulationDialog::getSettings() const
{
    SimulationSettings settings;
    int currentTab = tabWidget->currentIndex();

    if (currentTab == 0) { // Transient
        settings.type = SimulationSettings::Transient;
        settings.t_stop = stopTimeEdit->text().toDouble();
        settings.t_start = startTimeEdit->text().toDouble(); // <-- خواندن مقدار جدید
        settings.t_step = timeStepEdit->text().toDouble();
    } else if (currentTab == 1) { // AC Sweep
        settings.type = SimulationSettings::AC;
        settings.sweepType = (SimulationSettings::SweepType)sweepTypeCombo->currentIndex();
        settings.f_start = startFreqEdit->text().toDouble();
        settings.f_stop = stopFreqEdit->text().toDouble();
        settings.points = pointsEditAC->text().toInt();
    } else if (currentTab == 2) { // Phase Sweep
        settings.type = SimulationSettings::Phase;
        settings.base_freq = baseFreqEdit->text().toDouble();
        settings.p_start = startPhaseEdit->text().toDouble();
        settings.p_stop = stopPhaseEdit->text().toDouble();
        settings.points_phase = pointsEditPhase->text().toInt();
    }
    return settings;
}
