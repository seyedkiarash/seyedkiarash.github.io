#include "waveformsource.h"

WaveformSource::WaveformSource(QGraphicsItem *parent) : CircuitComponent(parent) {
    // Initialize with a default simple waveform for testing
    waveformData.push_back({0.0, 0.0});
    waveformData.push_back({0.5, 5.0});
    waveformData.push_back({1.0, 0.0});
}

void WaveformSource::setWaveformData(const std::vector<std::pair<double, double>>& data) {
    waveformData = data;
    // Ensure data is sorted by time, which is crucial for interpolation
    std::sort(waveformData.begin(), waveformData.end());
}

// This function calculates the voltage at a given time using linear interpolation
double WaveformSource::getVoltageAtTime(double time) {
    if (waveformData.empty()) {
        return 0.0; // No data, no voltage
    }
    if (time <= waveformData.front().first) {
        return waveformData.front().second; // Time is before the start
    }
    if (time >= waveformData.back().first) {
        return waveformData.back().second; // Time is after the end
    }

    // Find the two points to interpolate between
    for (size_t i = 0; i < waveformData.size() - 1; ++i) {
        if (time >= waveformData[i].first && time <= waveformData[i+1].first) {
            double t1 = waveformData[i].first;
            double v1 = waveformData[i].second;
            double t2 = waveformData[i+1].first;
            double v2 = waveformData[i+1].second;

            // Linear interpolation formula
            return v1 + (time - t1) * (v2 - v1) / (t2 - t1);
        }
    }
    return 0.0; // Should not be reached if data is sorted
}

void WaveformSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // A symbol for the waveform source (a circle with a wave)
    painter->setPen(QPen(Qt::black, 2));
    painter->drawEllipse(-20, -20, 40, 40);
    painter->drawLine(0, -20, 0, -30); // Top terminal
    painter->drawLine(0, 20, 0, 30);   // Bottom terminal

    // Draw a small wave symbol inside
    QPainterPath wavePath;
    wavePath.moveTo(-10, 0);
    wavePath.quadTo(-5, -10, 0, 0);
    wavePath.quadTo(5, 10, 10, 0);
    painter->drawPath(wavePath);
}

QRectF WaveformSource::boundingRect() const {
    return QRectF(-31, -31, 62, 62);
}