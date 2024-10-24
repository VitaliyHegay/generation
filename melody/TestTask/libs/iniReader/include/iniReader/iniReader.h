#ifndef INIREADER_H
#define INIREADER_H

#include <string>
#include <unordered_map>

class IniParser {
public:
    // Конструктор
    IniParser(const std::string& filePath);

    // Метод для парсинга файла
    bool parse();

    // Метод для получения значения по секции и ключу
    std::string getValue(const std::string& section, const std::string& key) const;

    // Метод для получения карты всех секций
    const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& getSections() const;

    // Метод для вывода данных (опционально для отладки)
    void print() const;

private:
    std::string filePath; // Путь к файлу
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> iniData; // Данные ini файла

    // Вспомогательный метод для удаления пробелов
    std::string trim(const std::string& str) const;
};

#endif // INIPARSER_H
