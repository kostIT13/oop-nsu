#include "utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<int> readFileToVector(const std::string& filename) {
    std::vector<int> vec;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return vec;
    }
    int value;
    while (file >> value) {
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