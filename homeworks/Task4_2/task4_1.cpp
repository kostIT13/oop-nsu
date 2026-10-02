#include "task4_1.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>

void solveTask4_1(const std::vector<int>& vecA, const std::vector<int>& vecB) {
    std::cout << "             ЗАДАНИЕ 4.I\n";

    std::vector<int> vecLarge, vecSmall;
    if (vecA.size() >= vecB.size()) {
        vecLarge = vecA;
        vecSmall = vecB;
    } else {
        vecLarge = vecB;
        vecSmall = vecA;
    }

    printVectorPreview(vecLarge, "Первый (больший) вектор");
    printVectorPreview(vecSmall, "Второй (меньший) вектор");
    std::cout << std::endl;

    std::cout << "Пункт 2: Количество чисел\n";
    std::cout << "Размер 1-го вектора: " << vecLarge.size() << std::endl;
    std::cout << "Размер 2-го вектора: " << vecSmall.size() << std::endl;

    std::cout << "\n--- Пункт 3: Частота встречаемости (топ-5 уникальных) ---\n";
    std::map<int, int> freqLarge, freqSmall;

    for (int x : vecLarge) freqLarge[x]++;
    for (int x : vecSmall) freqSmall[x]++;

    std::cout << "Способ 3a (цикл for) для 1-го вектора:\n";
    int count = 0;
    for (const auto& pair : freqLarge) {
        if (count++ >= 5) break;
        std::cout << "  Число " << pair.first << ": " << pair.second << " раз\n";
    }

    std::vector<int> uniqueLarge = vecLarge;
    std::sort(uniqueLarge.begin(), uniqueLarge.end());
    uniqueLarge.erase(std::unique(uniqueLarge.begin(), uniqueLarge.end()), uniqueLarge.end());

    std::cout << "Способ 3b (<algorithm>) для 1-го вектора:\n";
    count = 0;
    for (int val : uniqueLarge) {
        if (count++ >= 5) break;
        auto cnt = std::count(vecLarge.begin(), vecLarge.end(), val);
        std::cout << "  Число " << val << ": " << cnt << " раз\n";
    }

    // 4. Сумма всех значений (два варианта)
    std::cout << "\n--- Пункт 4: Сумма всех значений ---\n";
    long long sum1 = std::accumulate(vecLarge.begin(), vecLarge.end(), 0LL);
    long long sum2 = std::accumulate(vecLarge.begin(), vecLarge.end(), 0LL, [](long long a, int b) { return a + b; });
    std::cout << "Сумма 1-го вектора (accumulate): " << sum1 << std::endl;
    std::cout << "Сумма 1-го вектора (accumulate + lambda): " << sum2 << std::endl;

    // 5. Сумма первых 10 элементов без циклов
    std::cout << "\n--- Пункт 5: Сумма первых 10 элементов ---\n";
    size_t limit = std::min((size_t)10, vecLarge.size());
    long long sumFirst10 = std::accumulate(vecLarge.begin(), vecLarge.begin() + limit, 0LL);
    std::cout << "Сумма первых 10 элементов 1-го вектора: " << sumFirst10 << std::endl;
}