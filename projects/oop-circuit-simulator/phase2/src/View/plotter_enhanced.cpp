#include "plotter_enhanced.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QApplication>
#include <QPalette>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QtMath>

EnhancedPlotter::EnhancedPlotter(QWidget *parent)
    : QWidget(parent)
    , chart(nullptr)
    , chartView(nullptr)
    , xAxis(nullptr)
    , yAxis(nullptr)
    , autoScaleEnabled(true)
    , gridVisible(true)
    , legendVisible(true)
    , darkTheme(false)
    , cursorEnabled(false)
{
    setupUI();
    setupChart();
    setupControls();
    
    // Initialize color palette (LTSPICE-like colors)
    colorPalette = {
        QColor(255, 0, 0),      // Red
        QColor(0, 0, 255),      // Blue
        QColor(0, 128, 0),      // Green
        QColor(255, 165, 0),    // Orange
        QColor(128, 0, 128),    // Purple
        QColor(255, 192, 203),  // Pink
        QColor(0, 255, 255),    // Cyan
        QColor(255, 255, 0),    // Yellow
        QColor(128, 128, 128),  // Gray
        QColor(255, 0, 255),    // Magenta
        QColor(0, 255, 0),      // Lime
        QColor(255, 140, 0),    // Dark Orange
        QColor(75, 0, 130),     // Indigo
        QColor(255, 20, 147),   // Deep Pink
        QColor(0, 128, 128),    // Teal
        QColor(128, 0, 0),      // Maroon
        QColor(0, 0, 128),      // Navy
        QColor(128, 128, 0),    // Olive
        QColor(139, 69, 19),    // Saddle Brown
        QColor(47, 79, 79)      // Dark Slate Gray
    };
}

EnhancedPlotter::~EnhancedPlotter()
{
    // Clean up signals
    for (auto series : signals.values()) {
        delete series;
    }
    for (auto series : mathTraces.values()) {
        delete series;
    }
}
