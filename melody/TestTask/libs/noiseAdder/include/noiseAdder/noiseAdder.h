#ifndef NOISEADDER_H
#define NOISEADDER_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

class NoiseAdder {
private:
    double SNR;   // Соотношение сигнал/шум

public:
    std::vector<double> mixedSignal;

    // Конструктор
    NoiseAdder(double snr) : SNR(snr) {}

    // Добавление шума к сигналу
    void addNoise(const std::vector<double>& signal);

private:
    double calculatePower(const std::vector<double>& data);
};

#endif
