// =======================================================================
// FILE: componentdialog.cpp
// =======================================================================
#include "componentdialog.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QDialogButtonBox>
#include <QCoreApplication>
#include <QDir>

ComponentDialog::ComponentDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("انتخاب المان (Component)");
    setMinimumSize(300, 400);

    componentList = new QListWidget;
    populateList();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(componentList, &QListWidget::itemDoubleClicked, this, &QDialog::accept);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(componentList);
    mainLayout->addWidget(buttonBox);
}

void ComponentDialog::populateList()
{
    // اضافه کردن المان‌های پایه
    componentList->addItem("Resistor (مقاومت)");
    componentList->addItem("Capacitor (خازن)");
    componentList->addItem("Inductor (سلف)");
    componentList->addItem("Voltage Source (DC)");
    componentList->addItem("Current Source (DC)");
    componentList->addItem("Voltage Source (Sinusoidal)");
    componentList->addItem("Current Source (Sinusoidal)");
    componentList->addItem("Voltage Source (Pulse)");
    componentList->addItem("Current Source (Pulse)");
    componentList->addItem("Diode (دیود)");
    componentList->addItem("Zener Diode (دیود زنر)");
    componentList->addItem("Ground (زمین)");
    componentList->addItem("Wire (سیم)");

    // اضافه کردن یک جداکننده
    QListWidgetItem* separator = new QListWidgetItem("--- کتابخانه (Library) ---");
    separator->setFlags(Qt::NoItemFlags); // غیرقابل انتخاب
    componentList->addItem(separator);

    // اسکن و اضافه کردن تک‌قطبی‌های موجود
    QDir libraryDir(QCoreApplication::applicationDirPath() + "/library");
    QStringList filters;
    filters << "*.sub";
    libraryDir.setNameFilters(filters);
    QFileInfoList fileList = libraryDir.entryInfoList();
    for (const QFileInfo &fileInfo : fileList) {
        QListWidgetItem* item = new QListWidgetItem("SubCircuit: " + fileInfo.baseName());
        componentList->addItem(item);
    }
}

QString ComponentDialog::getSelectedComponent() const
{
    if (componentList->currentItem()) {
        QString text = componentList->currentItem()->text();
        if (text.startsWith("SubCircuit:")) {
             // برای تک‌قطبی‌ها، نام را استخراج می‌کنیم
            return text; // نام کامل را برمی‌گردانیم تا بعدا پردازش شود
        } else {
            // برای المان‌های پایه، فقط نام انگلیسی را برمی‌گردانیم
            return text.split(" ").first();
        }
    }
    return QString();
}
