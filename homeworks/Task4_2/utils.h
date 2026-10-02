#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

// Чтение чисел из файла в вектор
std::vector<int> readFileToVector(const std::string& filename);

// Красивый вывод первых N элементов вектора
void printVectorPreview(const std::vector<int>& v, const std::string& name, int n = 10);

#endif // UTILS_H