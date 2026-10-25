// =======================================================================
// FILE: plotter.cpp
// =======================================================================
#include "plotter.h"
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QValueAxis>
#include <QColorDialog>
#include <QMessageBox>
#include <QDebug>
#include <limits>
#include <functional>
#include <QMouseEvent>
#include <QtMath>
#include <QTimer>

// --- DataReader Implementation ---
DataReader::DataReader(const QString& path) : filePath(path) {}
void DataReader::process() {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit error("Cannot open data file: " + filePath);
        emit finished();
        return;
    }
    QTextStream in(&file);
    if(!in.atEnd()) {
        QString headerLine = in.readLine();
        QStringList headers = headerLine.split('\t', Qt::SkipEmptyParts);
        emit headersReady(headers);
    }
    QList<QList<QPointF>> dataChunks;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split('\t', Qt::SkipEmptyParts);
        if (parts.size() < 2) continue;
        double x_val = parts[0].toDouble();
        for(int i = 1; i < parts.size(); ++i) {
            if(dataChunks.size() <= (i-1)) dataChunks.append(QList<QPointF>());
            dataChunks[i-1].append(QPointF(x_val, parts[i].toDouble()));
        }
        if(!dataChunks.isEmpty() && dataChunks.first().size() >= 1000) {
            for(int i = 0; i < dataChunks.size(); ++i) emit dataChunkReady(dataChunks[i], i);
            dataChunks.clear();
        }
    }
    if(!dataChunks.isEmpty() && !dataChunks.first().isEmpty()){
        for(int i = 0; i < dataChunks.size(); ++i) emit dataChunkReady(dataChunks[i], i);
    }
    emit finished();
}

// --- Plotter Implementation ---
Plotter::Plotter(QWidget *parent) : QChartView(new QChart(), parent) {
    chart = QChartView::chart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    setRenderHint(QPainter::Antialiasing);
    setRubberBand(QChartView::RectangleRubberBand);
    setMouseTracking(true);
    cursorLine = new QGraphicsLineItem();
    cursorLine->setPen(QPen(QColor(255,255,0,128), 1, Qt::DashLine));
    scene()->addItem(cursorLine);
    cursorLine->hide();
}

void Plotter::handleLegendMarkerClicked() {
    QLegendMarker* marker = qobject_cast<QLegendMarker*>(sender());
    if (marker) {
        auto series = qobject_cast<QLineSeries*>(marker->series());
        if (!series) return;
        auto originalAnimationOptions = chart->animationOptions();
        chart->setAnimationOptions(QChart::NoAnimation);
        QColor color = QColorDialog::getColor(series->pen().color(), this, "انتخاب رنگ سیگنال");
        if (color.isValid()) {
            QPen pen = series->pen();
            pen.setColor(color);
            series->setPen(pen);
            if (!series->attachedAxes().isEmpty()) {
                QAbstractAxis* seriesAxis = series->attachedAxes().value(1);
                if (seriesAxis) seriesAxis->setLinePenColor(color);
            }
        }
        chart->setAnimationOptions(originalAnimationOptions);
    }
}

void Plotter::zoomIn() { 
    // زوم کلی با دکمه منو
    chart->zoom(1.2); 
    QTimer::singleShot(100, this, &Plotter::updateZoomRanges);
}
void Plotter::zoomOut() { 
    // زوم کلی با دکمه منو
    chart->zoom(1.0 / 1.2); 
    QTimer::singleShot(100, this, &Plotter::updateZoomRanges);
}
void Plotter::resetZoom() { 
    // ریست زوم با دکمه منو
    chart->zoomReset(); 
    QTimer::singleShot(100, this, &Plotter::updateZoomRanges);
}

void Plotter::autoZoom() {
    if (chart->series().isEmpty()) return;

    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY_L = std::numeric_limits<double>::max();
    double maxY_L = std::numeric_limits<double>::lowest();
    double minY_R = std::numeric_limits<double>::max();
    double maxY_R = std::numeric_limits<double>::lowest();

    bool leftAxisUsed = false;
    bool rightAxisUsed = false;

    for (QAbstractSeries *abstractSeries : chart->series()) {
        auto series = qobject_cast<QLineSeries*>(abstractSeries);
        if (!series || series->points().isEmpty()) continue;

        for (const QPointF &p : series->points()) {
            minX = qMin(minX, p.x());
            maxX = qMax(maxX, p.x());

            if (series->attachedAxes().contains(axisY_Left)) {
                minY_L = qMin(minY_L, p.y());
                maxY_L = qMax(maxY_L, p.y());
                leftAxisUsed = true;
            }
            if (series->attachedAxes().contains(axisY_Right)) {
                minY_R = qMin(minY_R, p.y());
                maxY_R = qMax(maxY_R, p.y());
                rightAxisUsed = true;
            }
        }
    }

    if (axisX) axisX->setRange(minX, maxX);
    if (leftAxisUsed && axisY_Left) {
        double margin = (maxY_L - minY_L) * 0.05; // 5% margin
        axisY_Left->setRange(minY_L - margin, maxY_L + margin);
    }
    if (rightAxisUsed && axisY_Right) {
        double margin = (maxY_R - minY_R) * 0.05;
        axisY_Right->setRange(minY_R - margin, maxY_R + margin);
    }
}

bool Plotter::isDarkMode() const { return chart->theme() == QChart::ChartThemeDark; }
void Plotter::setLightTheme() {
    chart->setTheme(QChart::ChartThemeLight);
    chart->legend()->setLabelColor(Qt::black);
    if(axisX) { axisX->setTitleBrush(Qt::black); axisX->setLabelsBrush(Qt::black); }
    if(axisY_Left) { axisY_Left->setTitleBrush(Qt::black); axisY_Left->setLabelsBrush(Qt::black); }
    if(axisY_Right) { axisY_Right->setTitleBrush(Qt::black); axisY_Right->setLabelsBrush(Qt::black); }
}
void Plotter::setDarkTheme() {
    chart->setTheme(QChart::ChartThemeDark);
    chart->legend()->setLabelColor(Qt::white);
    if(axisX) { axisX->setTitleBrush(Qt::white); axisX->setLabelsBrush(Qt::white); }
    if(axisY_Left) { axisY_Left->setTitleBrush(Qt::white); axisY_Left->setLabelsBrush(Qt::white); }
    if(axisY_Right) { axisY_Right->setTitleBrush(Qt::white); axisY_Right->setLabelsBrush(Qt::white); }
}
void Plotter::loadDataFromFile(const QString& filePath) {
    clearChart();
    QThread* thread = new QThread;
    DataReader* reader = new DataReader(filePath);
    reader->moveToThread(thread);
    connect(thread, &QThread::started, reader, &DataReader::process);
    connect(reader, &DataReader::finished, thread, &QThread::quit);
    connect(reader, &DataReader::finished, reader, &DataReader::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(reader, &DataReader::dataChunkReady, this, &Plotter::addDataChunk);
    connect(reader, &DataReader::headersReady, this, &Plotter::setupAxesAndLegend);
    thread->start();
}
void Plotter::setupAxesAndLegend(const QStringList& headers) {
    if (headers.size() < 2) return;
    axisX = new QValueAxis;
    axisX->setTitleText(headers[0]);
    chart->addAxis(axisX, Qt::AlignBottom);
    for (int i = 1; i < headers.size(); ++i) {
        auto series = new QLineSeries();
        series->setName(headers[i]);
        chart->addSeries(series);
        series->attachAxis(axisX);
        if (headers[i].toLower().contains('v')) {
            if (!axisY_Left) {
                axisY_Left = new QValueAxis;
                axisY_Left->setTitleText("Voltage (V)");
                chart->addAxis(axisY_Left, Qt::AlignLeft);
            }
            series->attachAxis(axisY_Left);
        } else if (headers[i].toLower().contains('i')) {
            if (!axisY_Right) {
                axisY_Right = new QValueAxis;
                axisY_Right->setTitleText("Current (A)");
                chart->addAxis(axisY_Right, Qt::AlignRight);
            }
            series->attachAxis(axisY_Right);
        }
    }
    for (QLegendMarker* marker : chart->legend()->markers()) {
        connect(marker, &QLegendMarker::clicked, this, &Plotter::handleLegendMarkerClicked);
    }
    isDarkMode() ? setDarkTheme() : setLightTheme();
}
void Plotter::addDataChunk(const QList<QPointF>& data, int seriesIndex) {
    if (chart->series().size() <= seriesIndex) {
        qWarning() << "Series index out of bounds";
        return;
    }
    auto series = static_cast<QLineSeries*>(chart->series().at(seriesIndex));
    series->append(data);
    if (series->points().size() == data.size()) {
        autoZoom();
    updateZoomRanges(); // پس از بارگذاری اولین تکه داده، زوم خودکار انجام شود
    }
}
void Plotter::clearChart() {
    chart->removeAllSeries();
    if(axisX) { chart->removeAxis(axisX); delete axisX; axisX = nullptr; }
    if(axisY_Left) { chart->removeAxis(axisY_Left); delete axisY_Left; axisY_Left = nullptr; }
    if(axisY_Right) { chart->removeAxis(axisY_Right); delete axisY_Right; axisY_Right = nullptr; }
    if (cursorLine) cursorLine->hide();
}

QStringList Plotter::getSignalNames() const {
    QStringList names;
    for (QAbstractSeries* s : chart->series()) names << s->name();
    return names;
}

static void combineSeriesPoints(const QVector<QPointF>& a, const QVector<QPointF>& b, QVector<QPointF>& out, const std::function<double(double,double)>& op) {
    if (a.isEmpty() || b.isEmpty()) return;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (qFuzzyCompare(a[i].x(), b[j].x())) {
            out.append(QPointF(a[i].x(), op(a[i].y(), b[j].y())));
            ++i; ++j;
        } else if (a[i].x() < b[j].x()) {
            ++i;
        } else {
            ++j;
        }
    }
}

void Plotter::addMathTrace(const QString& seriesNameA, const QString& seriesNameB, const QString& op, const QString& resultName) {
    QLineSeries* sa = nullptr; QLineSeries* sb = nullptr;
    for (QAbstractSeries* s : chart->series()) {
        auto ls = qobject_cast<QLineSeries*>(s);
        if (!ls) continue;
        if (ls->name() == seriesNameA) sa = ls;
        if (ls->name() == seriesNameB) sb = ls;
    }
    if (!sa || !sb) return;
    std::function<double(double,double)> f = [](double A, double B){ return A + B; };
    if (op == "+") f = [](double A, double B){ return A + B; }; else
    if (op == "-") f = [](double A, double B){ return A - B; }; else
    if (op == "*") f = [](double A, double B){ return A * B; }; else
    if (op == "/") f = [](double A, double B){ return (B == 0.0 ? 0.0 : A / B); };

    QVector<QPointF> out;
    combineSeriesPoints(sa->pointsVector(), sb->pointsVector(), out, f);
    auto sOut = new QLineSeries();
    sOut->setName(resultName);
    sOut->append(out);
    chart->addSeries(sOut);
    if (axisX) sOut->attachAxis(axisX);
    if (axisY_Left) sOut->attachAxis(axisY_Left);
    autoZoom();
    updateZoomRanges();
}

void Plotter::setCursorEnabled(bool enabled) {
    cursorEnabled = enabled;
    if (!cursorEnabled && cursorLine) cursorLine->hide();
}

double Plotter::interpolateSeriesY(QLineSeries* series, double x) const {
    const auto pts = series->pointsVector();
    if (pts.isEmpty()) return 0.0;
    if (x <= pts.first().x()) return pts.first().y();
    if (x >= pts.last().x()) return pts.last().y();
    for (int i = 0; i < pts.size() - 1; ++i) {
        if (x >= pts[i].x() && x <= pts[i+1].x()) {
            double x1 = pts[i].x(), y1 = pts[i].y();
            double x2 = pts[i+1].x(), y2 = pts[i+1].y();
            double t = (x - x1) / (x2 - x1);
            return y1 + t * (y2 - y1);
        }
    }
    return 0.0;
}

void Plotter::mouseMoveEvent(QMouseEvent *event) {
    QChartView::mouseMoveEvent(event);
    if (!cursorEnabled || !axisX || chart->series().isEmpty()) return;
    QPointF pos = event->pos();
    QPointF xOnChart = chart->mapToValue(pos, chart->series().first());
    double xVal = xOnChart.x();
    QPointF top = chart->mapToPosition(QPointF(xVal, 0), chart->series().first());
    QPointF bottom = top; bottom.setY(viewport()->height());
    if (cursorLine) {
        cursorLine->setLine(QLineF(QPointF(top.x(), 0), QPointF(top.x(), viewport()->height())));
        cursorLine->show();
    }
    QString text = QString("x=%1 ").arg(xVal, 0, 'g', 6);
    for (QAbstractSeries* s : chart->series()) {
        auto ls = qobject_cast<QLineSeries*>(s);
        if (!ls) continue;
        double y = interpolateSeriesY(ls, xVal);
        text += QString("%1=%2 ").arg(s->name()).arg(y, 0, 'g', 6);
    }
    emit cursorMoved(text.trimmed());
}

// =======================================================================
// متدهای جدید برای نمودارهای پیش‌فرض
// =======================================================================

void Plotter::addDefaultSineWave(const QString& name, const QColor& color) {
    auto series = new QLineSeries();
    series->setName(name);
    
    // تولید نقاط سینوسی (ولتاژ)
    const int numPoints = 1000;
    const double frequency = 1.0;  // 1 Hz
    const double amplitude = 5.0;  // 5V
    const double duration = 50.0;  // 50ms like LTSPICE
    
    for (int i = 0; i < numPoints; ++i) {
        double time = (double)i / (numPoints - 1) * duration;
        double value = amplitude * qSin(2.0 * M_PI * frequency * time / 1000.0); // Convert to ms
        series->append(time, value);
    }
    
    // تنظیم رنگ
    QPen pen(color);
    pen.setWidth(2);
    series->setPen(pen);
    
    // ایجاد محورها اگر وجود ندارند
    if (!axisX) {
        axisX = new QValueAxis;
        axisX->setTitleText("زمان (ms)");
        axisX->setRange(-duration * 0.05, duration * 1.05); // 5% حاشیه
        chart->addAxis(axisX, Qt::AlignBottom);
    }
    
    if (!axisY_Left) {
        axisY_Left = new QValueAxis;
        axisY_Left->setTitleText("ولتاژ (V)");
        axisY_Left->setRange(-amplitude * 1.3, amplitude * 1.3); // 30% حاشیه
        chart->addAxis(axisY_Left, Qt::AlignLeft);
    }
    
    // اضافه کردن به نمودار
    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY_Left);
    
    autoZoom();
    updateZoomRanges();
}

void Plotter::addDefaultDCWave(const QString& name, const QColor& color) {
    auto series = new QLineSeries();
    series->setName(name);
    
    // تولید نقاط DC (جریان ثابت)
    const int numPoints = 1000;
    const double dcValue = 300.0;  // 300µA
    const double duration = 50.0;  // 50ms
    
    for (int i = 0; i < numPoints; ++i) {
        double time = (double)i / (numPoints - 1) * duration;
        series->append(time, dcValue);
    }
    
    // تنظیم رنگ
    QPen pen(color);
    pen.setWidth(2);
    series->setPen(pen);
    
    // ایجاد محور راست برای جریان اگر وجود ندارد
    if (!axisY_Right) {
        axisY_Right = new QValueAxis;
        axisY_Right->setTitleText("جریان (µA)");
        axisY_Right->setRange(-dcValue * 0.1, dcValue * 1.6); // 10% حاشیه پایین، 60% بالا
        chart->addAxis(axisY_Right, Qt::AlignRight);
    }
    
    // اضافه کردن به نمودار
    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY_Right); // استفاده از محور راست برای جریان
    
    autoZoom();
    updateZoomRanges();
}

void Plotter::addDefaultCosineWave(const QString& name, const QColor& color) {
    auto series = new QLineSeries();
    series->setName(name);
    
    // تولید نقاط کسینوسی (ولتاژ)
    const int numPoints = 1000;
    const double frequency = 1.5;  // 1.5 Hz
    const double amplitude = 4.0;  // 4V
    const double duration = 50.0;  // 50ms
    
    for (int i = 0; i < numPoints; ++i) {
        double time = (double)i / (numPoints - 1) * duration;
        double value = amplitude * qCos(2.0 * M_PI * frequency * time / 1000.0); // Convert to ms
        series->append(time, value);
    }
    
    // تنظیم رنگ
    QPen pen(color);
    pen.setWidth(2);
    series->setPen(pen);
    
    // اضافه کردن به نمودار
    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY_Left); // استفاده از محور چپ برای ولتاژ
    
    autoZoom();
    updateZoomRanges();
}

void Plotter::changeChartColors() {
    showColorSelectionDialog();
}

void Plotter::showColorSelectionDialog() {
    if (chart->series().isEmpty()) {
        QMessageBox::information(this, "اطلاع", "هیچ نموداری برای تغییر رنگ وجود ندارد.");
        return;
    }
    
    // ایجاد دیالوگ انتخاب نمودار و رنگ
    QDialog dialog(this);
    dialog.setWindowTitle("تغییر رنگ نمودارها");
    dialog.setModal(true);
    dialog.resize(400, 300);
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    
    // لیست نمودارها
    QLabel* seriesLabel = new QLabel("انتخاب نمودار:");
    layout->addWidget(seriesLabel);
    
    QComboBox* seriesCombo = new QComboBox();
    for (QAbstractSeries* series : chart->series()) {
        seriesCombo->addItem(series->name());
    }
    layout->addWidget(seriesCombo);
    
    // انتخاب رنگ
    QLabel* colorLabel = new QLabel("انتخاب رنگ:");
    layout->addWidget(colorLabel);
    
    QList<QColor> predefinedColors = {
        QColor(255, 0, 0),    // قرمز
        QColor(0, 255, 0),    // سبز
        QColor(0, 0, 255),    // آبی
        QColor(255, 255, 0),  // زرد
        QColor(255, 0, 255),  // بنفش
        QColor(0, 255, 255),  // آبی روشن
        QColor(255, 165, 0),  // نارنجی
        QColor(128, 0, 128),  // بنفش تیره
        QColor(0, 128, 0),    // سبز تیره
        QColor(128, 128, 128) // خاکستری
    };
    
    QGridLayout* colorLayout = new QGridLayout();
    for (int i = 0; i < predefinedColors.size(); ++i) {
        QPushButton* colorBtn = new QPushButton();
        colorBtn->setFixedSize(30, 30);
        colorBtn->setStyleSheet(QString("background-color: %1; border: 1px solid black;").arg(predefinedColors[i].name()));
        colorBtn->setProperty("color", predefinedColors[i]);
        
        connect(colorBtn, &QPushButton::clicked, [this, seriesCombo, colorBtn]() {
            int seriesIndex = seriesCombo->currentIndex();
            if (seriesIndex >= 0 && seriesIndex < chart->series().size()) {
                QColor selectedColor = colorBtn->property("color").value<QColor>();
                auto lineSeries = qobject_cast<QLineSeries*>(chart->series().at(seriesIndex));
                if (lineSeries) {
                    QPen pen(selectedColor);
                    pen.setWidth(2);
                    lineSeries->setPen(pen);
                }
            }
        });
        
        colorLayout->addWidget(colorBtn, i / 5, i % 5);
    }
    
    QWidget* colorWidget = new QWidget();
    colorWidget->setLayout(colorLayout);
    layout->addWidget(colorWidget);
    
    // دکمه‌های OK و Cancel
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okBtn = new QPushButton("تایید");
    QPushButton* cancelBtn = new QPushButton("لغو");
    
    connect(okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);
    layout->addLayout(buttonLayout);
    
    dialog.exec();
}

// =======================================================================
// متدهای جدید برای زوم کامل و نمایش مختصات
// =======================================================================

void Plotter::updateZoomRanges() {
    // به‌روزرسانی محدوده‌های محورها بعد از زوم برای جلوگیری از برش
    if (chart->series().isEmpty()) return;
    
    // محاسبه محدوده‌های جدید
    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY_L = std::numeric_limits<double>::max();
    double maxY_L = std::numeric_limits<double>::lowest();
    double minY_R = std::numeric_limits<double>::max();
    double maxY_R = std::numeric_limits<double>::lowest();
    
    for (QAbstractSeries* series : chart->series()) {
        auto lineSeries = qobject_cast<QLineSeries*>(series);
        if (!lineSeries) continue;
        
        QList<QPointF> points = lineSeries->points();
        if (points.isEmpty()) continue;
        
        // محاسبه محدوده X
        for (const QPointF& point : points) {
            minX = qMin(minX, point.x());
            maxX = qMax(maxX, point.x());
        }
        
        // محاسبه محدوده Y بر اساس محور متصل
        QList<QAbstractAxis*> attachedAxes = lineSeries->attachedAxes();
        if (attachedAxes.size() >= 2) {
            QAbstractAxis* yAxis = attachedAxes[1];
            if (yAxis == axisY_Left) {
                for (const QPointF& point : points) {
                    minY_L = qMin(minY_L, point.y());
                    maxY_L = qMax(maxY_L, point.y());
                }
            } else if (yAxis == axisY_Right) {
                for (const QPointF& point : points) {
                    minY_R = qMin(minY_R, point.y());
                    maxY_R = qMax(maxY_R, point.y());
                }
            }
        }
    }
    
    // به‌روزرسانی محورها با حاشیه اضافی برای جلوگیری از برش
    if (axisX && minX != std::numeric_limits<double>::max()) {
        double xRange = maxX - minX;
        double xMargin = xRange * 0.05; // 5% حاشیه
        axisX->setRange(minX - xMargin, maxX + xMargin);
    }
    if (axisY_Left && minY_L != std::numeric_limits<double>::max()) {
        double yRange = maxY_L - minY_L;
        double yMargin = yRange * 0.1; // 10% حاشیه
        axisY_Left->setRange(minY_L - yMargin, maxY_L + yMargin);
    }
    if (axisY_Right && minY_R != std::numeric_limits<double>::max()) {
        double yRange = maxY_R - minY_R;
        double yMargin = yRange * 0.1; // 10% حاشیه
        axisY_Right->setRange(minY_R - yMargin, maxY_R + yMargin);
    }
}

void Plotter::showCoordinatesDialog(double x, double y, const QString& seriesName) {
    // تشخیص نوع محور Y
    QString yUnit = "V";
    QString yLabel = "ولتاژ";
    
    // بررسی اینکه آیا این سری از محور راست استفاده می‌کند
    for (QAbstractSeries* series : chart->series()) {
        if (series->name() == seriesName) {
            auto lineSeries = qobject_cast<QLineSeries*>(series);
            if (lineSeries) {
                QList<QAbstractAxis*> attachedAxes = lineSeries->attachedAxes();
                if (attachedAxes.size() >= 2 && attachedAxes[1] == axisY_Right) {
                    yUnit = "µA";
                    yLabel = "جریان";
                }
            }
            break;
        }
    }
    
    // ایجاد دیالوگ نمایش مختصات
    QDialog dialog(this);
    dialog.setWindowTitle("مختصات نقطه");
    dialog.setModal(true);
    dialog.resize(300, 150);
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    
    QLabel* titleLabel = new QLabel(QString("مختصات %1:").arg(seriesName));
    titleLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    layout->addWidget(titleLabel);
    
    QLabel* timeLabel = new QLabel(QString("زمان: %1 ms").arg(x, 0, 'f', 3));
    timeLabel->setStyleSheet("font-size: 12px;");
    layout->addWidget(timeLabel);
    
    QLabel* valueLabel = new QLabel(QString("%1: %2 %3").arg(yLabel).arg(y, 0, 'f', 3).arg(yUnit));
    valueLabel->setStyleSheet("font-size: 12px;");
    layout->addWidget(valueLabel);
    
    QPushButton* okBtn = new QPushButton("تایید");
    connect(okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    layout->addWidget(okBtn);
    
    dialog.exec();
}

void Plotter::onChartClicked(QMouseEvent* event) {
    if (event->button() != Qt::RightButton) return;
    
    // تبدیل مختصات ماوس به مختصات نمودار
    QPointF chartPos = chart->mapToValue(event->pos(), chart->series().first());
    
    // پیدا کردن نزدیک‌ترین نقطه در نمودارها
    double minDistance = std::numeric_limits<double>::max();
    QString closestSeriesName;
    QPointF closestPoint;
    
    for (QAbstractSeries* series : chart->series()) {
        auto lineSeries = qobject_cast<QLineSeries*>(series);
        if (!lineSeries) continue;
        
        QList<QPointF> points = lineSeries->points();
        for (const QPointF& point : points) {
            double distance = qSqrt(qPow(point.x() - chartPos.x(), 2) + qPow(point.y() - chartPos.y(), 2));
            if (distance < minDistance) {
                minDistance = distance;
                closestSeriesName = series->name();
                closestPoint = point;
            }
        }
    }
    
    // نمایش مختصات اگر فاصله مناسب باشد
    if (minDistance < 5.0) { // حساسیت کلیک
        if (doubleCursorMode) {
            // حالت دابل کرسر
            if (!cursor1Set) {
                cursor1 = closestPoint;
                cursorSeriesName = closestSeriesName;
                cursor1Set = true;
                updateStatusBar("کرسر 1 تنظیم شد. نقطه دوم را انتخاب کنید.");
            } else if (!cursor2Set) {
                cursor2 = closestPoint;
                cursor2Set = true;
                showDoubleCursorDialog(cursor1, cursor2, cursorSeriesName);
                // ریست برای انتخاب بعدی
                cursor1Set = false;
                cursor2Set = false;
            }
        } else {
            // حالت عادی - نمایش مختصات
            showCoordinatesDialog(closestPoint.x(), closestPoint.y(), closestSeriesName);
        }
    }
}

void Plotter::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        // فقط برای کلیک راست - نمایش مختصات
        onChartClicked(event);
    } else {
        // برای کلیک چپ - زوم عادی
        QChartView::mousePressEvent(event);
    }
}

// =======================================================================
// متدهای اسکیل جداگانه برای هر محور
// =======================================================================

void Plotter::scaleXAxis(double factor) {
    if (!axisX) return;
    
    double currentMin = axisX->min();
    double currentMax = axisX->max();
    double center = (currentMin + currentMax) / 2.0;
    double range = (currentMax - currentMin) / factor;
    
    axisX->setRange(center - range/2, center + range/2);
}

void Plotter::scaleYLeftAxis(double factor) {
    if (!axisY_Left) return;
    
    double currentMin = axisY_Left->min();
    double currentMax = axisY_Left->max();
    double center = (currentMin + currentMax) / 2.0;
    double range = (currentMax - currentMin) / factor;
    
    axisY_Left->setRange(center - range/2, center + range/2);
}

void Plotter::scaleYRightAxis(double factor) {
    if (!axisY_Right) return;
    
    double currentMin = axisY_Right->min();
    double currentMax = axisY_Right->max();
    double center = (currentMin + currentMax) / 2.0;
    double range = (currentMax - currentMin) / factor;
    
    axisY_Right->setRange(center - range/2, center + range/2);
}

// =======================================================================
// متدهای دابل کرسر
// =======================================================================

void Plotter::enableDoubleCursor() {
    doubleCursorMode = true;
    cursor1Set = false;
    cursor2Set = false;
    updateStatusBar("حالت دابل کرسر فعال شد. دو نقطه را با کلیک راست انتخاب کنید.");
}

void Plotter::disableDoubleCursor() {
    doubleCursorMode = false;
    cursor1Set = false;
    cursor2Set = false;
    updateStatusBar("حالت دابل کرسر غیرفعال شد.");
}

void Plotter::showDoubleCursorDialog(const QPointF& point1, const QPointF& point2, const QString& seriesName) {
    // تشخیص نوع محور Y
    QString yUnit = "V";
    QString yLabel = "ولتاژ";
    
    // بررسی اینکه آیا این سری از محور راست استفاده می‌کند
    for (QAbstractSeries* series : chart->series()) {
        if (series->name() == seriesName) {
            auto lineSeries = qobject_cast<QLineSeries*>(series);
            if (lineSeries) {
                QList<QAbstractAxis*> attachedAxes = lineSeries->attachedAxes();
                if (attachedAxes.size() >= 2 && attachedAxes[1] == axisY_Right) {
                    yUnit = "µA";
                    yLabel = "جریان";
                }
            }
            break;
        }
    }
    
    // محاسبه اختلافات
    double deltaX = point2.x() - point1.x();
    double deltaY = point2.y() - point1.y();
    double slope = (deltaX != 0) ? deltaY / deltaX : 0;
    double frequency = (deltaX != 0) ? 1000.0 / deltaX : 0; // تبدیل به Hz
    
    // ایجاد دیالوگ دابل کرسر
    QDialog dialog(this);
    dialog.setWindowTitle("دابل کرسر - " + seriesName);
    dialog.setModal(true);
    dialog.resize(400, 300);
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    
    // عنوان
    QLabel* titleLabel = new QLabel(QString("دابل کرسر - %1").arg(seriesName));
    titleLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    layout->addWidget(titleLabel);
    
    // جدول اطلاعات
    QGridLayout* gridLayout = new QGridLayout();
    
    // کرسر 1
    QLabel* cursor1Label = new QLabel("کرسر 1:");
    cursor1Label->setStyleSheet("font-weight: bold;");
    gridLayout->addWidget(cursor1Label, 0, 0);
    
    QLabel* cursor1HorzLabel = new QLabel(QString("Horz: %1 ms").arg(point1.x(), 0, 'f', 3));
    gridLayout->addWidget(cursor1HorzLabel, 1, 0);
    
    QLabel* cursor1VertLabel = new QLabel(QString("Vert: %1 %2").arg(point1.y(), 0, 'f', 3).arg(yUnit));
    gridLayout->addWidget(cursor1VertLabel, 2, 0);
    
    // کرسر 2
    QLabel* cursor2Label = new QLabel("کرسر 2:");
    cursor2Label->setStyleSheet("font-weight: bold;");
    gridLayout->addWidget(cursor2Label, 0, 1);
    
    QLabel* cursor2HorzLabel = new QLabel(QString("Horz: %1 ms").arg(point2.x(), 0, 'f', 3));
    gridLayout->addWidget(cursor2HorzLabel, 1, 1);
    
    QLabel* cursor2VertLabel = new QLabel(QString("Vert: %1 %2").arg(point2.y(), 0, 'f', 3).arg(yUnit));
    gridLayout->addWidget(cursor2VertLabel, 2, 1);
    
    // اختلافات
    QLabel* diffLabel = new QLabel("اختلاف:");
    diffLabel->setStyleSheet("font-weight: bold;");
    gridLayout->addWidget(diffLabel, 3, 0);
    
    QLabel* diffHorzLabel = new QLabel(QString("Horz: %1 ms").arg(deltaX, 0, 'f', 3));
    gridLayout->addWidget(diffHorzLabel, 4, 0);
    
    QLabel* diffVertLabel = new QLabel(QString("Vert: %1 %2").arg(deltaY, 0, 'f', 3).arg(yUnit));
    gridLayout->addWidget(diffVertLabel, 5, 0);
    
    QLabel* freqLabel = new QLabel(QString("Freq: %1 Hz").arg(frequency, 0, 'f', 2));
    gridLayout->addWidget(freqLabel, 6, 0);
    
    QLabel* slopeLabel = new QLabel(QString("Slope: %1 %2/ms").arg(slope, 0, 'f', 3).arg(yUnit));
    gridLayout->addWidget(slopeLabel, 7, 0);
    
    layout->addLayout(gridLayout);
    
    // دکمه‌های OK و Cancel
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okBtn = new QPushButton("تایید");
    QPushButton* cancelBtn = new QPushButton("لغو");
    
    connect(okBtn, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);
    layout->addLayout(buttonLayout);
    
    dialog.exec();
}// =======================================================================
// تغییر نام سیگنال
// =======================================================================

void Plotter::showRenameSignalDialog() {
    if (chart->series().isEmpty()) {
        QMessageBox::information(this, "اطلاع", "هیچ سیگنالی برای تغییر نام وجود ندارد.");
        return;
    }
    
    // ایجاد دیالوگ تغییر نام
    QDialog dialog(this);
    dialog.setWindowTitle("تغییر نام سیگنال");
    dialog.setModal(true);
    dialog.resize(400, 200);
    
    QVBoxLayout* layout = new QVBoxLayout(&dialog);
    
    // انتخاب سیگنال
    QLabel* signalLabel = new QLabel("انتخاب سیگنال:");
    layout->addWidget(signalLabel);
    
    QComboBox* signalCombo = new QComboBox();
    for (QAbstractSeries* series : chart->series()) {
        signalCombo->addItem(series->name());
    }
    layout->addWidget(signalCombo);
    
    // نام جدید
    QLabel* nameLabel = new QLabel("نام جدید:");
    layout->addWidget(nameLabel);
    
    QLineEdit* nameEdit = new QLineEdit();
    nameEdit->setPlaceholderText("نام جدید سیگنال را وارد کنید...");
    layout->addWidget(nameEdit);
    
    // به‌روزرسانی نام جدید هنگام تغییر سیگنال
    connect(signalCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), [nameEdit, signalCombo](int index) {
        if (index >= 0) {
            nameEdit->setText(signalCombo->itemText(index));
        }
    });
    
    // تنظیم نام اولیه
    if (signalCombo->count() > 0) {
        nameEdit->setText(signalCombo->itemText(0));
    }
    
    // دکمه‌های OK و Cancel
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okBtn = new QPushButton("تایید");
    QPushButton* cancelBtn = new QPushButton("لغو");
    
    connect(okBtn, &QPushButton::clicked, [&dialog, signalCombo, nameEdit, this]() {
        int signalIndex = signalCombo->currentIndex();
        QString newName = nameEdit->text().trimmed();
        
        if (signalIndex >= 0 && !newName.isEmpty()) {
            // تغییر نام سیگنال
            QAbstractSeries* series = chart->series().at(signalIndex);
            series->setName(newName);
            
            // به‌روزرسانی لیست سیگنال‌ها
            signalCombo->setItemText(signalIndex, newName);
            
            QMessageBox::information(&dialog, "موفق", QString("نام سیگنال به '%1' تغییر یافت.").arg(newName));
        } else {
            QMessageBox::warning(&dialog, "خطا", "لطفاً نام جدید را وارد کنید.");
            return;
        }
        
        dialog.accept();
    });
    
    connect(cancelBtn, &QPushButton::clicked, &dialog, &QDialog::reject);
    
    buttonLayout->addWidget(okBtn);
    buttonLayout->addWidget(cancelBtn);
    layout->addLayout(buttonLayout);
    
    dialog.exec();
}
