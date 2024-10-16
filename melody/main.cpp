#include "generator/generator.h"
#include "noiseAdder/noiseAdder.h"
#include "wavwritter/wavwritter.h"
#include "wavplay/wavplay.h"

#include <iostream>

int main() {
    setlocale(LC_ALL, "");

    std::cout << "Hello, World!" << std::endl;
    std::cout << "Шаг 0: Задание переменных" << std::endl;
    // Параметры
    double frequency = 1000.0;  // Частота сигнала
    double duration = 4.0;    // Длительность (в секундах)
    int sampleRate = 44100;    // Частота дискретизации (Гц)
    double SNR = 3.0;        // Соотношение сигнал/шум в дБ

    // Генерация сигнала
    std::cout << "Шаг 1: Генерация сигнала" << std::endl;
    SignalGenerator::foo();
    SignalGenerator generator(frequency, duration, sampleRate);
    generator.generateSignal();

    // Добавление шума
    std::cout << "Шаг 2: Добавление шума" << std::endl;
    NoiseAdder noiseAdder(SNR);
    noiseAdder.addNoise(generator.signal);

    // Запись в WAV файл
    std::cout << "Шаг 3: Запись в формате WAV" << std::endl;
    WavWriter writer(sampleRate, 16, 1);  // Частота, битность, число каналов (моно)
    std::string filename = "D:\\UNIVER\\9 semestr\\RadioMonitoring\\generation\\mixed_signal_C.wav";
    writer.writeWavFile(filename, noiseAdder.mixedSignal);

    // Воспроизведение WAV файла через Windows Media Player
    std::cout << "Шаг 4: Запуск WAV-файла" << std::endl;
    playWavFile(filename);

    return 0;
}

