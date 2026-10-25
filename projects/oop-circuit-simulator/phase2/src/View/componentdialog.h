// =======================================================================
// FILE: componentdialog.h
// =======================================================================
// این کلاس دیالوگ انتخاب المان مدار را پیاده‌سازی می‌کند.
//========================================================================
#ifndef COMPONENTDIALOG_H
#define COMPONENTDIALOG_H

#include <QDialog>

class QListWidget;
class QDialogButtonBox;

class ComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ComponentDialog(QWidget *parent = nullptr);
    QString getSelectedComponent() const;

private:
    void populateList();

    QListWidget *componentList;
    QDialogButtonBox *buttonBox;
    QString selectedComponent;
};

#endif // COMPONENTDIALOG_H
