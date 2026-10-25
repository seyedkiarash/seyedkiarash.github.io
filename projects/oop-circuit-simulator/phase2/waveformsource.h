#ifndef WAVEFORMSOURCE_H
#define WAVEFORMSOURCE_H

#include "circuitcomponent.h"
#include <vector>
#include <utility> // For std::pair
#include <algorithm> // For std::sort

class WaveformSource : public CircuitComponent {
public:
    WaveformSource(QGraphicsItem *parent = nullptr);

    // Method to set the waveform data from outside
    void setWaveformData(const std::vector<std::pair<double, double>>& data);

    // Method for the simulator to get voltage at a specific time
    double getVoltageAtTime(double time);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

private:
    // This vector will store the <time, voltage> data points
    std::vector<std::pair<double, double>> waveformData;
};

#endif // WAVEFORMSOURCE_H