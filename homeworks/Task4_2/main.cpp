#include <iostream>
#include <vector>
#include <windows.h>   
#include "utils.h"
#include "task4_1.h"
#include "task4_2.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    std::vector<int> vec1 = readFileToVector("s04_v1_46_1.txt");
    std::vector<int> vec2 = readFileToVector("s04_v1_46_2.txt");

    if (vec1.empty() || vec2.empty()) {
        std::cerr << "Ошибка: Не удалось прочитать данные. Проверьте input1.txt и input2.txt." << std::endl;
        return 1;
    }

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