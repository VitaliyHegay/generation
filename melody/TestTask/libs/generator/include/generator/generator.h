#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

class SignalGenerator {
private:
    double frequency;     // Частота сигнала
    double duration;      // Длительность сигнала
    int sampleRate;       // Частота дискретизации
    double SNR;           // Соотношение сигнал/шум

public:
    std::vector<double> signal;
    std::vector<double> mixedSignal;

    // Конструктор
    SignalGenerator(double freq, double dur, int rate, double snr)
        : frequency(freq), duration(dur), sampleRate(rate), SNR(snr) {}

    // Генерация синусоидального сигнала
    void generateSignal() {
        int numSamples = static_cast<int>(duration * sampleRate);
        signal.resize(numSamples);
        for (int i = 0; i < numSamples; ++i) {
            signal[i] = sin(2.0 * M_PI * frequency * i / sampleRate);
        }
    }

    // Генерация шума и аддитивной смеси
    void addNoise() {
        int numSamples = signal.size();
        mixedSignal.resize(numSamples);
        double signalPower = calculatePower(signal);
        double noisePower = signalPower / pow(10.0, SNR / 10.0);

        std::srand(std::time(nullptr)); // Инициализация случайных чисел

        for (int i = 0; i < numSamples; ++i) {
            double noise = sqrt(noisePower) * ((rand() / (double)RAND_MAX) - 0.5);
            mixedSignal[i] = signal[i] + noise;
        }
    }

    // Подсчет мощности сигнала
    double calculatePower(const std::vector<double>& data) {
        double power = 0.0;

        //if (data.empty()) return 0.0; // Защита от деления на ноль

        for (double x : data) {
            power += x * x;
        }
        return power / data.size();
    }
};

#endif
