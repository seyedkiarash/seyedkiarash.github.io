// =======================================================================
// FILE: simulationdialog.h
// =======================================================================
// این کلاس دیالوگ تنظیمات شبیه‌سازی را با تب‌های جداگانه تعریف می‌کند.
//========================================================================
#ifndef SIMULATIONDIALOG_H
#define SIMULATIONDIALOG_H

#include <QDialog>
#include "datatypes.h"

// Forward declaration to avoid including heavy headers
class QTabWidget;
class QDialogButtonBox;
class QLineEdit;
class QComboBox;

class SimulationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationDialog(QWidget *parent = nullptr);

    // متد عمومی برای گرفتن تنظیمات وارد شده توسط کاربر
    SimulationSettings getSettings() const;

private:
    // ویجت‌های اصلی
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;

    // ویجت‌های تب تحلیل گذرا (Transient)
    QLineEdit *stopTimeEdit;
    QLineEdit *startTimeEdit; // <-- ویجت جدید برای زمان شروع
    QLineEdit *timeStepEdit;

    // ویجت‌های تب تحلیل فرکانسی (AC Sweep)
    QComboBox *sweepTypeCombo;
    QLineEdit *startFreqEdit;
    QLineEdit *stopFreqEdit;
    QLineEdit *pointsEditAC;

    // ویجت‌های تب تحلیل فاز (Phase Sweep)
    QLineEdit *baseFreqEdit;
    QLineEdit *startPhaseEdit;
    QLineEdit *stopPhaseEdit;
    QLineEdit *pointsEditPhase;
};

#endif // SIMULATIONDIALOG_H
