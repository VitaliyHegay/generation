#include "generator/generator.h"
#include "wavwritter/wavwritter.h"
#include "wavplay/wavplay.h"

int main() {
    // Параметры
    double frequency = 1000.0;  // Частота сигнала
    double duration = 5.0;    // Длительность (в секундах)
    int sampleRate = 46000;    // Частота дискретизации (Гц)
    double SNR = 60.0;        // Соотношение сигнал/шум в дБ

    // Генерация сигнала
    SignalGenerator generator(frequency, duration, sampleRate, SNR);
    generator.generateSignal();
    generator.addNoise();

    // Запись в WAV файл
    WavWriter writer(sampleRate, 16, 1);  // Частота, битность, число каналов (моно)
    std::string filename = "D:\\UNIVER\\9 semestr\\RadioMonitoring\\generation\\mixed_signal_C.wav";
    writer.writeWavFile(filename, generator.mixedSignal);

    // Воспроизведение WAV файла через Windows Media Player
    playWavFile(filename);

    return 0;
}

