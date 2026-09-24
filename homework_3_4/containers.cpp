#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <random>
#include <cmath>
#include <sstream>

constexpr int M = 14;       
constexpr int N = 2;        
using T1 = double;        
using T2 = int;             

// ===== Генератор случайных чисел =====
std::mt19937 rng(std::random_device{}());

T1 randomT1() {
    std::uniform_real_distribution<double> dist(-static_cast<double>(N),
                                                 static_cast<double>(N));
    return dist(rng);
}

// ===== "Расширенная модифицированная" функция (задание 3.I) =====
// ВНИМАНИЕ: замените формулу на свою из задания 3.I.
// Здесь пример: f(x, k) = x * k + |x|, результат приводится к int
T2 extendedFunction(T1 x, T1 k) {
    double result = x * k + std::abs(x);
    return static_cast<T2>(std::round(result));
}

// ===== Вспомогательная функция: строка таблицы =====
std::string makeRow(const std::vector<std::string>& cells) {
    std::ostringstream oss;
    oss << "|";
    for (const auto& c : cells) {
        oss << " " << c << " |";
    }
    return oss.str();
}

std::string fmt(T1 v) {
    std::ostringstream s;
    s << std::fixed << std::setprecision(3) << v;
    return s.str();
}

int main() {
    std::cout << "=== Лабораторная работа: контейнеры и циклы ===\n";
    std::cout << "T1=double, T2=int, M=" << M << ", N=" << N << "\n\n";

    // Второй аргумент функции — генерируется один раз и постоянен
    T1 k = randomT1();
    std::cout << "Случайный параметр k = " << fmt(k) << "\n\n";

    // ===== 1. Создание и заполнение контейнеров (3 формы for) =====
    std::array<T1, M> arr{};
    std::vector<T1> vec(M);
    std::list<T1> lst(M);
    std::deque<T1> deq(M);

    // array — классическая форма for
    for (size_t i = 0; i < M; ++i) {
        arr[i] = randomT1();
    }

    // vector — форма с итераторами
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        *it = randomT1();
    }

    // list — range-based for
    for (auto& v : lst) {
        v = randomT1();
    }

    // deque — классическая форма for (или итераторы)
    for (size_t i = 0; i < M; ++i) {
        deq[i] = randomT1();
    }

    // ===== 2. Применение функции; результат — в контейнеры другого типа =====
    // array  -> vector<T2>
    std::vector<T2> arrResult;
    for (const auto& v : arr) {
        arrResult.push_back(extendedFunction(v, k));
    }

    // vector -> list<T2>
    std::list<T2> vecResult;
    for (const auto& v : vec) {
        vecResult.push_back(extendedFunction(v, k));
    }

    // list   -> deque<T2>
    std::deque<T2> lstResult;
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        lstResult.push_back(extendedFunction(*it, k));
    }

    // deque  -> vector<T2>
    std::vector<T2> deqResult;
    for (size_t i = 0; i < M; ++i) {
        deqResult.push_back(extendedFunction(deq[i], k));
    }

    // ===== 3. Формирование строк таблицы (один цикл for) =====
    std::vector<std::string> rows;

    auto itArr  = arr.begin();
    auto itVec  = vec.begin();
    auto itLst  = lst.begin();
    auto itDeq  = deq.begin();

    auto itArrR = arrResult.begin();
    auto itVecR = vecResult.begin();
    auto itLstR = lstResult.begin();
    auto itDeqR = deqResult.begin();

    for (int i = 0; i < M; ++i) {
        std::vector<std::string> cells;
        cells.push_back(std::to_string(i));

        // исходные значения (T1 = double)
        cells.push_back(fmt(*itArr));
        cells.push_back(fmt(*itVec));
        cells.push_back(fmt(*itLst));
        cells.push_back(fmt(*itDeq));

        // результаты (T2 = int)
        cells.push_back(std::to_string(*itArrR));
        cells.push_back(std::to_string(*itVecR));
        cells.push_back(std::to_string(*itLstR));
        cells.push_back(std::to_string(*itDeqR));

        rows.push_back(makeRow(cells));

        ++itArr; ++itVec; ++itLst; ++itDeq;
        ++itArrR; ++itVecR; ++itLstR; ++itDeqR;
    }

    // ===== 4. Формирование md-таблицы =====
    std::ostringstream md;
    md << "# Результаты лабораторной работы\n\n";
    md << "**Параметры:** T1=double, T2=int, M=" << M
       << ", N=" << N << ", k=" << fmt(k) << "\n\n";

    md << "| # | array (T1) | vector (T1) | list (T1) | deque (T1) "
       << "| array->vector (T2) | vector->list (T2) | list->deque (T2) | deque->vector (T2) |\n";

    md << "|---|------------|-------------|-----------|------------|"
          "--------------------|-------------------|-------------------|---------------------|\n";

    for (const auto& r : rows) {
        md << r << "\n";
    }

    // ===== 5. Запись в файл =====
    const std::string filename = "result.md";
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Не удалось открыть файл " << filename << "\n";
        return 1;
    }
    out << md.str();
    out.close();

    std::cout << "Таблица записана в файл: " << filename << "\n\n";
    std::cout << "=== Содержимое md-файла ===\n";
    std::cout << md.str();

    return 0;
}