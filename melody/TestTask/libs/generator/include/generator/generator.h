#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <cmath>


class SignalGenerator {
private:
    double A;         // Амплитуда сигнала
    double f0;     // Частота сигнала
    double dT;      // Длительность сигнала
    int Fs;       // Частота дискретизации

public:
    // Конструктор
    SignalGenerator(double amp, double freq, double dur, int rate);
    static int foo();
    // Генерация синусоидального сигнала
    std::vector<double> generateSignal();
};

#endif
