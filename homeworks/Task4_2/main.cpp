#include <iostream>
#include <vector>
#include <string>
#include "tasks.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<int> vec1 = readFileToVector("s04_v1_46_1.txt");
    std::vector<int> vec2 = readFileToVector("s04_v1_46_2.txt");

    if (vec1.empty() || vec2.empty()) {
        std::cerr << "Ошибка: Не удалось прочитать данные из файлов. Проверьте наличие input1.txt и input2.txt." << std::endl;
        return 1;
    }

    solveTask4_1(vec1, vec2);

    solveTask4_2(vec1, vec2);

    return 0;
}