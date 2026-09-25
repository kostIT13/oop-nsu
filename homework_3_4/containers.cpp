#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <deque>
#include <random>
#include <sstream>
#include <utility>

template <typename R, typename T>
R average(T a, T b) {
    R ra = static_cast<R>(a);
    R rb = static_cast<R>(b);
    return (ra + rb) / static_cast<R>(2);
}

template <typename R, typename T>
R mode_average(const T& a, const T& b) {
    static std::mt19937 gen(std::random_device{}());
    R ra = static_cast<R>(a);
    R rb = static_cast<R>(b);
    R result = (ra + rb) / static_cast<R>(2);
    if (std::bernoulli_distribution(0.5)(gen))
        result += static_cast<R>(std::uniform_int_distribution<int>(-10, 10)(gen));
    return result;
}

int main() {
    constexpr std::size_t M = 8;    // длина контейнеров
    constexpr int N = 50;           // диапазон [-N, N]
    using T1 = int;                 // тип входных элементов
    using T2 = double;              // тип результата

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<T1> dist(-N, N);

    // Постоянный второй аргумент
    T1 secondArg = dist(gen);
    std::cout << "Постоянный второй аргумент: " << secondArg << "\n\n";

    std::array<T1, M> arr;
    std::vector<T1> vec(M);
    std::list<T1> lst;
    std::deque<T1> deq;

    for (std::size_t i = 0; i < M; ++i) {
        T1 v = dist(gen);
        arr[i] = v;
        vec[i] = v;
        lst.push_back(v);
        deq.push_back(v);
    }

    std::vector<T2> vecRes(M);   // из array  -> vector
    std::list<T2>   listRes;     // из vector -> list
    std::deque<T2>  deqRes;      // из list   -> deque
    std::vector<T2> vecRes2;     // из deque  -> vector

    for (std::size_t i = 0; i < arr.size(); ++i)
        vecRes[i] = mode_average<T2>(arr[i], secondArg);

    for (auto it = vec.begin(); it != vec.end(); ++it)
        listRes.push_back(mode_average<T2>(*it, secondArg));

    for (const auto& x : lst)
        deqRes.push_back(mode_average<T2>(x, secondArg));

    for (const auto& x : deq)
        vecRes2.push_back(mode_average<T2>(x, secondArg));

    std::vector<T1> arrVec(arr.begin(), arr.end());
    std::vector<T1> lstVec(lst.begin(), lst.end());
    std::vector<T1> deqVec(deq.begin(), deq.end());
    std::vector<T2> listResVec(listRes.begin(), listRes.end());
    std::vector<T2> deqResVec(deqRes.begin(), deqRes.end());

    using RowPair = std::pair<const std::vector<T1>*, const std::vector<T2>*>;
    std::vector<std::pair<std::string, RowPair>> table = {
        {"array<int>",  {&arrVec,     &vecRes    }},
        {"vector<int>", {&vec,        &listResVec}},
        {"list<int>",   {&lstVec,     &deqResVec }},
        {"deque<int>",  {&deqVec,     &vecRes2   }}
    };

    std::vector<std::string> rows;
    for (const auto& entry : table) {
        std::ostringstream oss;
        oss << "| " << entry.first << " ";
        for (std::size_t i = 0; i < M; ++i)
            oss << "| " << (*entry.second.first)[i] << " ";
        oss << "| ";
        for (std::size_t i = 0; i < M; ++i)
            oss << "| " << std::fixed << std::setprecision(2)
                << (*entry.second.second)[i] << " ";
        oss << "|";
        rows.push_back(oss.str());
    }

    std::ofstream fout("table.md");
    if (!fout) { std::cerr << "Не удалось открыть файл\n"; return 1; }

    fout << "| Контейнер ";
    for (std::size_t i = 0; i < M; ++i) fout << "| T1[" << i << "] ";
    fout << "| ";
    for (std::size_t i = 0; i < M; ++i) fout << "| T2[" << i << "] ";
    fout << "|\n";

    fout << "|---";
    for (std::size_t i = 0; i < M; ++i) fout << "|---";
    fout << "|---";
    for (std::size_t i = 0; i < M; ++i) fout << "|---";
    fout << "|\n";

    for (const auto& r : rows) fout << r << "\n";

    fout.close();
    std::cout << "Таблица записана в table.md\n";
    return 0;
}