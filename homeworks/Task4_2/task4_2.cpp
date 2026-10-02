#include "task4_2.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>
#include <functional>

void solveTask4_2(const std::vector<int>& vecLarge, const std::vector<int>& vecSmall) {
    std::cout << "             ЗАДАНИЕ 4.II\n";

    // 1. Бинарная операция (умножение) с std::accumulate
    std::cout << "--- Пункт 1: Бинарная операция (умножение) ---\n";
    long long productLarge = std::accumulate(vecLarge.begin(), vecLarge.end(), 1LL, std::multiplies<long long>());
    long long productSmall = std::accumulate(vecSmall.begin(), vecSmall.end(), 1LL, std::multiplies<long long>());
    std::cout << "Произведение 1-го вектора: " << productLarge << std::endl;
    std::cout << "Произведение 2-го вектора: " << productSmall << std::endl;

    // 2. Определение дубликатов
    std::cout << "\n--- Пункт 2: Поиск дубликатов ---\n";
    std::map<int, int> freqLarge, freqSmall;
    for (int x : vecLarge) freqLarge[x]++;
    for (int x : vecSmall) freqSmall[x]++;

    std::vector<int> dupSmall;
    for (const auto& pair : freqSmall) {
        if (pair.second >= 2) dupSmall.push_back(pair.first);
    }

    std::vector<int> dupLarge;
    for (const auto& pair : freqLarge) {
        if (pair.second > 3) dupLarge.push_back(pair.first);
    }

    std::cout << "Числа во 2-м векторе (>=2 раз): ";
    for (int n : dupSmall) std::cout << n << " ";
    std::cout << "\nЧисла в 1-м векторе (>3 раз): ";
    for (int n : dupLarge) std::cout << n << " ";
    std::cout << std::endl;

    // 3. Сравнение дубликатов
    std::cout << "\n--- Пункт 3: Сравнение дубликатов ---\n";
    
    std::cout << "Способ A (цикл for):\n";
    for (int val : dupLarge) {
        int countInSmall = 0;
        for (int x : vecSmall) {
            if (x == val) countInSmall++;
        }
        std::cout << "  Число " << val << ": в 1-м векторе " << freqLarge[val] 
                  << " раз, во 2-м векторе " << countInSmall << " раз.\n";
    }

    std::cout << "Способ B (<algorithm> + lambda):\n";
    for (int val : dupLarge) {
        auto countInSmall = std::count_if(vecSmall.begin(), vecSmall.end(), 
                                          [val](int x) { return x == val; });
        std::cout << "  Число " << val << ": в 1-м векторе " << freqLarge[val] 
                  << " раз, во 2-м векторе " << countInSmall << " раз.\n";
    }
}