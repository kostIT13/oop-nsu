#include "tasks.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <map>
#include <functional>
#include <iomanip>

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

void printVectorPreview(const std::vector<int>& v, const std::string& name, int n = 10) {
    std::cout << name << " (размер: " << v.size() << "): ";
    for (int i = 0; i < std::min((int)v.size(), n); ++i) {
        std::cout << v[i] << " ";
    }
    if (v.size() > (size_t)n) std::cout << "...";
    std::cout << std::endl;
}

void solveTask4_1(const std::vector<int>& vecA, const std::vector<int>& vecB) {
    std::cout << "\n==========================================\n";
    std::cout << "             ЗАДАНИЕ 4.I\n";
    std::cout << "==========================================\n";

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

    std::cout << "--- Пункт 2: Количество чисел ---\n";
    std::cout << "Размер 1-го вектора: " << vecLarge.size() << std::endl;
    std::cout << "Размер 2-го вектора: " << vecSmall.size() << std::endl;

    std::cout << "\n--- Пункт 3: Частота встречаемости (топ-5) ---\n";
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

    std::cout << "\n--- Пункт 4: Сумма всех значений ---\n";
    long long sum1 = std::accumulate(vecLarge.begin(), vecLarge.end(), 0LL);
    long long sum2 = std::accumulate(vecLarge.begin(), vecLarge.end(), 0LL, [](long long a, int b) { return a + b; });
    std::cout << "Сумма 1-го вектора (accumulate): " << sum1 << std::endl;
    std::cout << "Сумма 1-го вектора (accumulate + lambda): " << sum2 << std::endl;

    std::cout << "\n--- Пункт 5: Сумма первых 10 элементов ---\n";
    size_t limit = std::min((size_t)10, vecLarge.size());
    long long sumFirst10 = std::accumulate(vecLarge.begin(), vecLarge.begin() + limit, 0LL);
    std::cout << "Сумма первых 10 элементов 1-го вектора: " << sumFirst10 << std::endl;
}

void solveTask4_2(const std::vector<int>& vecLarge, const std::vector<int>& vecSmall) {
    std::cout << "\n==========================================\n";
    std::cout << "             ЗАДАНИЕ 4.II\n";
    std::cout << "==========================================\n";

    std::cout << "--- Пункт 1: Бинарная операция (умножение) ---\n";
    long long productLarge = std::accumulate(vecLarge.begin(), vecLarge.end(), 1LL, std::multiplies<long long>());
    long long productSmall = std::accumulate(vecSmall.begin(), vecSmall.end(), 1LL, std::multiplies<long long>());
    std::cout << "Произведение 1-го вектора: " << productLarge << std::endl;
    std::cout << "Произведение 2-го вектора: " << productSmall << std::endl;

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