#ifndef PLOTTER_ENHANCED_H
#define PLOTTER_ENHANCED_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QMap>
#include <QString>
#include <QColor>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QSlider>
#include <QCheckBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QDoubleSpinBox>

QT_CHARTS_USE_NAMESPACE

class EnhancedPlotter : public QWidget
{
    Q_OBJECT

public:
    explicit EnhancedPlotter(QWidget *parent = nullptr);
    ~EnhancedPlotter();

    // Signal management
    void clearSignals();
    void addSignal(const QString& name, const QVector<double>& xData, const QVector<double>& yData, const QColor& color = QColor());
    void removeSignal(const QString& name);
    QStringList getSignalNames() const;
    
    // Math operations
    void addMathTrace(const QString& expression);
    void removeMathTrace(const QString& name);
    
    // Display settings
    void setAutoScale(bool enabled);
    void setGridVisible(bool visible);
    void setLegendVisible(bool visible);
    void setTheme(bool darkTheme);
    
    // Zoom and pan
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void fitToView();
    
    // Cursor functionality
    void enableCursor(bool enabled);
    void setCursorPosition(double x, double y);
    
    // Export
    void exportToImage(const QString& filename);
    void exportToCSV(const QString& filename);

signals:
    void cursorMoved(double x, double y, const QMap<QString, double>& values);
    void signalAdded(const QString& name);
    void signalRemoved(const QString& name);

private slots:
    void onZoomInClicked();
    void onZoomOutClicked();
    void onResetZoomClicked();
    void onFitToViewClicked();
    void onAutoScaleToggled(bool checked);
    void onGridToggled(bool checked);
    void onLegendToggled(bool checked);
    void onThemeChanged(bool dark);
    void onCursorToggled(bool checked);
    void onSignalSelectionChanged(const QString& signalName);
    void onMathExpressionChanged();
    void onCursorMoved(const QPointF& pos);

private:
    void setupUI();
    void setupChart();
    void setupControls();
    void updateChartTheme();
    void calculateMathTrace(const QString& expression);
    QColor generateSignalColor(int index);
    void updateCursorDisplay();
    
    // Chart components
    QChart* chart;
    QChartView* chartView;
    QValueAxis* xAxis;
    QValueAxis* yAxis;
    
    // Signal management
    QMap<QString, QLineSeries*> signals;
    QMap<QString, QVector<double>> signalDataX;
    QMap<QString, QVector<double>> signalDataY;
    QMap<QString, QColor> signalColors;
    QMap<QString, QLineSeries*> mathTraces;
    
    // Control widgets
    QPushButton* zoomInBtn;
    QPushButton* zoomOutBtn;
    QPushButton* resetZoomBtn;
    QPushButton* fitToViewBtn;
    QCheckBox* autoScaleCheck;
    QCheckBox* gridCheck;
    QCheckBox* legendCheck;
    QCheckBox* cursorCheck;
    QComboBox* signalSelector;
    QComboBox* mathExpressionCombo;
    QSpinBox* cursorXSpin;
    QSpinBox* cursorYSpin;
    QLabel* cursorValueLabel;
    
    // Settings
    bool autoScaleEnabled;
    bool gridVisible;
    bool legendVisible;
    bool darkTheme;
    bool cursorEnabled;
    
    // Cursor state
    QPointF cursorPosition;
    QMap<QString, double> cursorValues;
    
    // Color palette for signals (LTSPICE-like)
    QVector<QColor> colorPalette;
    
    static const int MAX_SIGNALS = 20;
};

#endif // PLOTTER_ENHANCED_H
