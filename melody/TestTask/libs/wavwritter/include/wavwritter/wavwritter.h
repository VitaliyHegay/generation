#ifndef WAVWRITER_H
#define WAVWRITER_H

#include <string>
#include <vector>
#include <fstream>
#include <cstdint>

class WavWriter {
private:
    const int sampleRate;
    const int bitsPerSample;
    const int numChannels;

public:
    WavWriter(int rate, int bits, int channels)
        : sampleRate(rate), bitsPerSample(bits), numChannels(channels) {}

    void writeWavFile(const std::string& filename, const std::vector<double>& signal) {
        std::ofstream file(filename, std::ios::binary);

        // Заголовок WAV
        int dataSize = signal.size() * sizeof(int16_t);
        writeWavHeader(file, dataSize);

        // Запись данных (преобразование double в int16_t)
        for (double sample : signal) {
            int16_t sampleInt = static_cast<int16_t>(sample * 32767);
            file.write(reinterpret_cast<const char*>(&sampleInt), sizeof(sampleInt));
        }

        file.close();
    }

private:
    void writeWavHeader(std::ofstream& file, int dataSize) {
        // RIFF заголовок
        file.write("RIFF", 4);
        int32_t chunkSize = 36 + dataSize;
        file.write(reinterpret_cast<const char*>(&chunkSize), 4);
        file.write("WAVE", 4);

        // fmt подзаголовок
        file.write("fmt ", 4);
        int32_t subChunk1Size = 16;
        file.write(reinterpret_cast<const char*>(&subChunk1Size), 4);
        int16_t audioFormat = 1;  // PCM
        file.write(reinterpret_cast<const char*>(&audioFormat), 2);
        file.write(reinterpret_cast<const char*>(&numChannels), 2);
        file.write(reinterpret_cast<const char*>(&sampleRate), 4);
        int32_t byteRate = sampleRate * numChannels * bitsPerSample / 8;
        file.write(reinterpret_cast<const char*>(&byteRate), 4);
        int16_t blockAlign = numChannels * bitsPerSample / 8;
        file.write(reinterpret_cast<const char*>(&blockAlign), 2);
        file.write(reinterpret_cast<const char*>(&bitsPerSample), 2);

        // data подзаголовок
        file.write("data", 4);
        file.write(reinterpret_cast<const char*>(&dataSize), 4);
    }
};

#endif
