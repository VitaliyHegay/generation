#include "generator.h"
#include <iostream>

SignalGenerator::SignalGenerator(double freq, double dur, int rate)
    : frequency(freq), duration(dur), sampleRate(rate) {

    std::cout<<__FUNCTION__<<std::endl;
}

int SignalGenerator::foo(){
    return 10;
}

void SignalGenerator::generateSignal() {
    int numSamples = static_cast<int>(duration * sampleRate);
    signal.resize(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        signal[i] = sin(2.0 * M_PI * frequency * i / sampleRate);
    }
}
