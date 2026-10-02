#include "task4_1.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>

void solveTask4_1(const std::vector<int>& vecLarge, const std::vector<int>& vecSmall) {
    std::cout << "             ЗАДАНИЕ 4.I\n";

    // 1. Информация о векторах
    printVectorPreview(vecLarge, "Первый (больший) вектор");
    printVectorPreview(vecSmall, "Второй (меньший) вектор");
    std::cout << std::endl;

    // 2. Подсчет количества чисел
    std::cout << "--- Пункт 2: Количество чисел ---\n";
    std::cout << "Размер 1-го вектора: " << vecLarge.size() << std::endl;
    std::cout << "Размер 2-го вектора: " << vecSmall.size() << std::endl;

    // 3. Частота встречаемости
    std::cout << "\n--- Пункт 3: Частота встречаемости (топ-5) ---\n";
    std::map<int, int> freqLarge;
    std::map<int, int> freqSmall;

    // 3a. Способ через цикл for
    for (int i = 0; i < (int)vecLarge.size(); ++i) {
        freqLarge[vecLarge[i]]++;
    }
    for (int i = 0; i < (int)vecSmall.size(); ++i) {
        freqSmall[vecSmall[i]]++;
    }

    std::cout << "Способ 3a (цикл for) для 1-го вектора:\n";
    int count = 0;
    for (std::map<int, int>::iterator it = freqLarge.begin(); it != freqLarge.end(); ++it) {
        if (count++ >= 5) break;
        std::cout << "  Число " << it->first << ": " << it->second << " раз\n";
    }

    // 3b. Способ через <algorithm>
    std::vector<int> uniqueLarge = vecLarge;
    std::sort(uniqueLarge.begin(), uniqueLarge.end());
    std::vector<int>::iterator last = std::unique(uniqueLarge.begin(), uniqueLarge.end());
    uniqueLarge.erase(last, uniqueLarge.end());

    std::cout << "Способ 3b (<algorithm>) для 1-го вектора:\n";
    count = 0;
    for (int i = 0; i < (int)uniqueLarge.size(); ++i) {
        if (count++ >= 5) break;
        int val = uniqueLarge[i];
        int cnt = (int)std::count(vecLarge.begin(), vecLarge.end(), val);
        std::cout << "  Число " << val << ": " << cnt << " раз\n";
    }

    // 4. Сумма всех значений
    std::cout << "\n--- Пункт 4: Сумма всех значений ---\n";
    long long sum1 = std::accumulate(vecLarge.begin(), vecLarge.end(), 0LL);
    long long sum2 = std::accumulate(vecLarge.begin(), vecLarge.end(), 0LL,
                                     [](long long acc, int x) { return acc + x; });
    std::cout << "Сумма 1-го вектора (accumulate): " << sum1 << std::endl;
    std::cout << "Сумма 1-го вектора (accumulate + lambda): " << sum2 << std::endl;

    // 5. Сумма первых 10 элементов
    std::cout << "\n--- Пункт 5: Сумма первых 10 элементов ---\n";
    int limit = std::min(10, (int)vecLarge.size());
    long long sumFirst10 = std::accumulate(vecLarge.begin(), vecLarge.begin() + limit, 0LL);
    std::cout << "Сумма первых 10 элементов 1-го вектора: " << sumFirst10 << std::endl;
}