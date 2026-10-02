#include <iostream>
#include <vector>
#include <windows.h>  // для SetConsoleOutputCP (только Windows)
#include "utils.h"
#include "task4_1.h"
#include "task4_2.h"

int main() {
    // Настраиваем UTF-8 вывод в консоль Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 1. Чтение данных из файлов
    std::vector<int> vec1 = readFileToVector("s04_v1_46_1.txt");
    std::vector<int> vec2 = readFileToVector("s04_v1_46_2.txt");

    if (vec1.empty() || vec2.empty()) {
        std::cerr << "Ошибка: не удалось прочитать данные. Проверьте input1.txt и input2.txt." << std::endl;
        return 1;
    }

    // Определяем больший и меньший вектор
    std::vector<int> vecLarge;
    std::vector<int> vecSmall;
    if (vec1.size() >= vec2.size()) {
        vecLarge = vec1;
        vecSmall = vec2;
    } else {
        vecLarge = vec2;
        vecSmall = vec1;
    }

    // 2. Запуск задания 4.I
    solveTask4_1(vecLarge, vecSmall);

    // 3. Запуск задания 4.II
    solveTask4_2(vecLarge, vecSmall);

    return 0;
}