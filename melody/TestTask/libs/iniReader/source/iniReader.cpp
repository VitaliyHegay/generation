#include "iniReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Конструктор
IniParser::IniParser(const std::string& filePath) : filePath(filePath) {}

// Метод для парсинга файла
bool IniParser::parse() {
    std::ifstream configFile(filePath);

    if (!configFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filePath << "!" << std::endl;
        return false;
    }

    std::string line;
    std::string currentSection;

    // Чтение файла построчно
    while (std::getline(configFile, line)) {
        // Убираем пробелы в начале и конце строки
        line = trim(line);

        // Пропускаем пустые строки и комментарии
        if (line.empty() || line[0] == '!' || line[0] == '#') {
            continue;
        }

        // Если строка определяет секцию (например, [global])
        if (line[0] == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        // Если строка содержит ключ=значение
        else if (line.find('=') != std::string::npos) {
            size_t pos = line.find('=');
            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1));

            // Сохраняем ключ и значение в структуру данных
            iniData[currentSection][key] = value;
        }
    }

    configFile.close();
    return true;
}

// Метод для получения карты всех секций
const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& IniParser::getSections() const {
    return iniData;
}

// Метод для получения значения по секции и ключу
std::string IniParser::getValue(const std::string& section, const std::string& key) const {
    if (iniData.find(section) != iniData.end()) {
        auto sectionMap = iniData.at(section);
        if (sectionMap.find(key) != sectionMap.end()) {
            return sectionMap.at(key);
        }
    }
    return ""; // Возвращает пустую строку, если ключ или секция не найдены
}

// Вспомогательный метод для удаления пробелов
std::string IniParser::trim(const std::string& str) const {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

// Метод для вывода данных
void IniParser::print() const {
    for (const auto& section : iniData) {
        std::cout << "[" << section.first << "]" << std::endl;
        for (const auto& kv : section.second) {
            std::cout << kv.first << " = " << kv.second << std::endl;
        }
        std::cout << std::endl;
    }
}
