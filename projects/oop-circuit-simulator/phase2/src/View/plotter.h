// =======================================================================
// FILE: plotter.h
// =======================================================================
#ifndef PLOTTER_H
#define PLOTTER_H

#include <QtCharts>
#include <QChartView>
#include <QObject>
#include <QGraphicsLineItem>

class DataReader : public QObject {
    Q_OBJECT
public:
    explicit DataReader(const QString& path);

    public slots:
        void process();

    signals:
        void dataChunkReady(const QList<QPointF>& data, int seriesIndex);
    void headersReady(const QStringList& headers);
    void finished();
    void error(const QString& err);

private:
    QString filePath;
};


class Plotter : public QChartView {
    Q_OBJECT
public:
    explicit Plotter(QWidget *parent = nullptr);

    public slots:
        void loadDataFromFile(const QString& filePath);
    void addDataChunk(const QList<QPointF>& data, int seriesIndex);
    void setupAxesAndLegend(const QStringList& headers);
    void clearChart();
    void setDarkTheme();
    void setLightTheme();
    void zoomIn();
    void zoomOut();
    void resetZoom();
    void autoZoom(); // <-- اسلات جدید برای زوم خودکار
    QStringList getSignalNames() const;
    void addMathTrace(const QString& seriesNameA, const QString& seriesNameB, const QString& op, const QString& resultName);
    void setCursorEnabled(bool enabled);
    bool isCursorEnabled() const { return cursorEnabled; }
    
    // متدهای جدید برای نمودارهای پیش‌فرض
    void addDefaultSineWave(const QString& name, const QColor& color);
    void addDefaultDCWave(const QString& name, const QColor& color);
    void addDefaultCosineWave(const QString& name, const QColor& color);
    void changeChartColors();
    void showColorSelectionDialog();
    void showCoordinatesDialog(double x, double y, const QString& seriesName);
    
    // تغییر نام سیگنال‌ها
    void updateZoomRanges();
    void onChartClicked(QMouseEvent* event);
    void scaleXAxis(double factor);
    void scaleYLeftAxis(double factor);
    void scaleYRightAxis(double factor);
    
    // دابل کرسر
    void enableDoubleCursor();
    void disableDoubleCursor();
    void showDoubleCursorDialog(const QPointF& point1, const QPointF& point2, const QString& seriesName);
    
    // تغییر نام سیگنال
    void showRenameSignalDialog();
    
    // Override mouse events
    void mousePressEvent(QMouseEvent* event) override;

    private slots:
        void handleLegendMarkerClicked();

signals:
    void cursorMoved(const QString& text);
    void updateStatusBar(const QString& message);

private:
    bool isDarkMode() const;
    QChart *chart;
    QValueAxis *axisX = nullptr;
    QValueAxis *axisY_Left = nullptr;
    QValueAxis *axisY_Right = nullptr;
    QGraphicsLineItem* cursorLine = nullptr;
    
    // دابل کرسر
    bool doubleCursorMode = false;
    QPointF cursor1;
    QPointF cursor2;
    QString cursorSeriesName;
    bool cursor1Set = false;
    bool cursor2Set = false;
    bool cursorEnabled = true;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    double interpolateSeriesY(QLineSeries* series, double x) const;
};

#endif // PLOTTER_H
