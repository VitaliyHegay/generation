#include "noiseAdder.h"

void NoiseAdder::addNoise(const std::vector<double>& signal) {
    int numSamples = signal.size();
    mixedSignal.resize(numSamples);
    double signalPower = calculatePower(signal);
    double noisePower = signalPower / pow(10.0, SNR / 10.0);

    std::srand(std::time(nullptr)); // Инициализация генератора случайных чисел

    for (int i = 0; i < numSamples; ++i) {
        double noise = sqrt(noisePower) * ((rand() / (double)RAND_MAX) - 0.5);
        mixedSignal[i] = signal[i] + noise;
    }
}

double NoiseAdder::calculatePower(const std::vector<double>& data) {
    double power = 0.0;
    for (double x : data) {
        power += x * x;
    }
    return power / data.size();
}
