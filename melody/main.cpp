#include "iniReader/iniReader.h"
#include "generator/generator.h"
#include "noiseAdder/noiseAdder.h"
#include "wavwritter/wavwritter.h"
#include "wavplay/wavplay.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <regex>  // Для работы с регулярными выражениями
#include <cstdlib>  // Для конвертации строк в числа
#include <vector>

int main() {
    //        double f0 = 1000.0;  // Частота сигнала
    //        double dT = 4.0;    // Длительность (в секундах)
    //        int Fs = 44100;    // Частота дискретизации (Гц)
            double SNR = 60.0;        // Соотношение сигнал/шум в дБ

    // Открываем файл для чтения
    IniParser parser("D:\\UNIVER\\9 semestr\\RadioMonitoring\\generation\\melody\\InputPar.ini");

    parser.parse();
//    parser.print();

    if (!parser.parse()) {
        std::cerr << "Error при разборе файла." << std::endl;
        return 1;
    }

    std::cout << "Step 0: Задание переменных" << std::endl;

    // Получаем значения
    std::string T = parser.getValue("global", "T");
    std::string Fs = parser.getValue("global", "Fs");
    // Преобразуем глобальные значения в числовой формат
    double globalT = std::stod(T);
    double globalFs = std::stod(Fs);

    // Создаем базовый вектор с количеством отсчетов, равным globalT * globalFs
    int numSamples = static_cast<int>(globalT * globalFs);
    std::vector<double> base(numSamples, 0.0);  // Инициализируем нулями

    // Получаем карту всех секций
    const auto& sections = parser.getSections();

    std::cout << "Step 1: Генерация сигнала" << std::endl;
    for (const auto& section : sections) {
        const std::string& sectionName = section.first;

        // Пропускаем секции [global] и [s.n]
        if (sectionName == "global") {
            continue;
        }
        std::regex regex("^s\\.\\d+$");
        if (!std::regex_match(sectionName, regex)) {
            continue;
        }

        // Обрабатываем секции
        std::cout << "Section: [" << sectionName << "]" << std::endl;
        // Получаем значения
        std::string A_str = parser.getValue(section.first, "A");
        std::string dT_str = parser.getValue(section.first, "dT");
        std::string T0_str = parser.getValue(section.first, "T0");
        std::string f0_str = parser.getValue(section.first, "F0");
        // Преобразуем строки в числа
        double A = std::stod(A_str);
        double dT = std::stod(dT_str);
        double T0 = std::stod(T0_str);
        double f0 = std::stod(f0_str);

        // Генерация сигнала
//        SignalGenerator::foo();
        SignalGenerator generator(A, f0, dT, globalFs);
        std::vector<double> signal = generator.generateSignal();

        // Вычисляем индекс начала T0 в отсчетах
        int startIndex = static_cast<int>(T0 * globalFs);

        // Добавляем сигнал в базовый вектор с учетом сдвига T0
        for (std::vector<double>::size_type i = 0; i < signal.size(); ++i) {
            if (startIndex + i < static_cast<std::vector<double>::size_type>(numSamples)) {
                base[startIndex + i] += signal[i];
            } else {
                break;  // Выходим из цикла, если сигнал выходит за пределы базового вектора
            }
        }
    }
    std::cout << "Success" << std::endl;

        // Добавление шума
        std::cout << "Step 2: Добавление шума" << std::endl;
        NoiseAdder noiseAdder(SNR);
        noiseAdder.addNoise(base);

        // Запись в WAV файл
        std::cout << "Step 3: Запись в формате WAV" << std::endl;
        WavWriter writer(globalFs, 16, 1);  // Частота, битность, число каналов (моно)
        std::string filename = "D:\\UNIVER\\9 semestr\\RadioMonitoring\\generation\\melody_C.wav";
        writer.writeWavFile(filename, noiseAdder.mixedSignal);

        // Воспроизведение WAV файла через Windows Media Player
        std::cout << "Step 4: Запуск WAV-файла" << std::endl;
        playWavFile(filename);

    return 0;
}

