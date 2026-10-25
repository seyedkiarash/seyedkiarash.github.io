// =======================================================================
// FILE: pch.h (Optimized Precompiled Header)
// =======================================================================
#ifndef PCH_H
#define PCH_H

// فقط کتابخانه‌های ضروری Qt
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtCharts>

// کتابخانه‌های استاندارد C++
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <cmath>

// فقط در صورت نیاز
#ifdef QT_CHARTS_LIB
#include <QtCharts>
#endif

#ifdef QT_NETWORK_LIB
#include <QtNetwork>
#endif

#endif // PCH_H
