// =======================================================================
// FILE: main.cpp
// =======================================================================
// نقطه شروع برنامه Qt. این فایل یک نمونه از MainWindow را ایجاد و نمایش می‌دهد.
//========================================================================
#include "mainwindow.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // تنظیم آیکون کلی برنامه از فایل منابع
    a.setWindowIcon(QIcon(":/resources/icon.svg"));

    MainWindow w;
    w.show();
    return a.exec();
}
