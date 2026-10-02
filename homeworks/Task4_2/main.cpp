#include <iostream>
#include <vector>
#include "utils.h"
#include "task4_1.h"
#include "task4_2.h"

int main() {
    setlocale(LC_ALL, "Russian"); // Для корректного отображения кириллицы в консоли Windows

    // 1. Чтение данных из файлов
    std::vector<int> vec1 = readFileToVector("input1.txt");
    std::vector<int> vec2 = readFileToVector("input2.txt");

    if (vec1.empty() || vec2.empty()) {
        std::cerr << "Ошибка: Не удалось прочитать данные. Проверьте input1.txt и input2.txt." << std::endl;
        return 1;
    }

    // Определяем больший и меньший вектор один раз здесь, чтобы передать в оба задания
    std::vector<int> vecLarge, vecSmall;
    if (vec1.size() >= vec2.size()) {
        vecLarge = vec1;
        vecSmall = vec2;
    } else {
        vecLarge = vec2;
        vecSmall = vec1;
    }

    // 2. Запуск Задания 4.I
    solveTask4_1(vecLarge, vecSmall);

    // 3. Запуск Задания 4.II
    solveTask4_2(vecLarge, vecSmall);

    return 0;
}