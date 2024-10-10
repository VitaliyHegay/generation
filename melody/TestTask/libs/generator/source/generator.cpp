#include "generator.h"

void SignalGenerator::generateSignal() {
    int numSamples = static_cast<int>(duration * sampleRate);
    signal.resize(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        signal[i] = sin(2.0 * M_PI * frequency * i / sampleRate);
    }
}
