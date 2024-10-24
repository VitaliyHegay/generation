#include "generator.h"
#include <iostream>

SignalGenerator::SignalGenerator(double amp, double freq, double dur, int rate)
    : A(amp), f0(freq), dT(dur), Fs(rate) {

    std::cout<<__FUNCTION__<<std::endl;
}

int SignalGenerator::foo(){
    return 10;
}

std::vector<double> SignalGenerator::generateSignal() {
    int numSamples = static_cast<int>(dT * Fs);
    std::vector<double> signal(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        signal[i] = A * sin(2.0 * M_PI * f0 * i / Fs);
    }
    return signal;
}
