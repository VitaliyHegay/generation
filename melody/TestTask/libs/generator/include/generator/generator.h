#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <cmath>

class SignalGenerator {
private:
    double frequency;     // Частота сигнала
    double duration;      // Длительность сигнала
    int sampleRate;       // Частота дискретизации

public:
    std::vector<double> signal;

    // Конструктор
    SignalGenerator(double freq, double dur, int rate)
        : frequency(freq), duration(dur), sampleRate(rate) {}

    // Генерация синусоидального сигнала
    void generateSignal();
};

#endif
