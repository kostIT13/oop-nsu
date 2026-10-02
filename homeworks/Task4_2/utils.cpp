#include "utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

std::vector<int> readFileToVector(const std::string& filename) {
    std::vector<int> vec;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return vec;
    }
    
    // Читаем весь файл как одну строку
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    
    // Заменяем все запятые на пробелы
    std::replace(content.begin(), content.end(), ',', ' ');
    
    // Теперь парсим числа из строки
    std::stringstream ss(content);
    int value;
    while (ss >> value) {
        vec.push_back(value);
    }
    
    return vec;
}

void printVectorPreview(const std::vector<int>& v, const std::string& name, int n) {
    std::cout << name << " (размер: " << v.size() << "): ";
    for (int i = 0; i < std::min((int)v.size(), n); ++i) {
        std::cout << v[i] << " ";
    }
    if (v.size() > (size_t)n) std::cout << "...";
    std::cout << std::endl;
}