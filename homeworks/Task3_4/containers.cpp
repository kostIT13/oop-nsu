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
    constexpr std::size_t M = 14;   // длина контейнеров
    constexpr int N = 2;            // диапазон [-N, N]
    typedef double T1;              // тип входных элементов
    typedef int    T2;              // тип результата

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<T1> dist(-N, N);

    T1 secondArg = dist(gen);
    std::cout << secondArg << "\n\n";

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

    std::vector<T1>::iterator itVec;
    for (itVec = vec.begin(); itVec != vec.end(); ++itVec)
        listRes.push_back(mode_average<T2>(*itVec, secondArg));

    for (const T1& x : lst)
        deqRes.push_back(mode_average<T2>(x, secondArg));

    for (const T1& x : deq)
        vecRes2.push_back(mode_average<T2>(x, secondArg));

    std::list<T2>::iterator itList = listRes.begin();
    std::list<T2>::iterator itLast = listRes.begin();

    for (; itList != listRes.end(); ++itList)
        itLast = itList;   

    std::cout << "last value " << *itLast << "\n\n";

    std::cout << "listRes: ";  
    std::list<T2>::iterator itPrint;
    for (itPrint = listRes.begin(); itPrint != listRes.end(); ++itPrint)
        std::cout << *itPrint << " ";
    std::cout << "\n";

    std::vector<T1> arrVec(arr.begin(), arr.end());
    std::vector<T1> lstVec(lst.begin(), lst.end());
    std::vector<T1> deqVec(deq.begin(), deq.end());
    std::vector<T2> listResVec(listRes.begin(), listRes.end());
    std::vector<T2> deqResVec(deqRes.begin(), deqRes.end());

    typedef std::pair<const std::vector<T1>*, const std::vector<T2>*> RowPair;
    std::vector<std::pair<std::string, RowPair>> table;
    table.push_back(std::make_pair(std::string("array<double>"),  RowPair(&arrVec,     &vecRes    )));
    table.push_back(std::make_pair(std::string("vector<double>"), RowPair(&vec,        &listResVec)));
    table.push_back(std::make_pair(std::string("list<double>"),   RowPair(&lstVec,     &deqResVec )));
    table.push_back(std::make_pair(std::string("deque<double>"),  RowPair(&deqVec,     &vecRes2   )));

    std::vector<std::string> rows;
    std::vector<std::pair<std::string, RowPair>>::const_iterator itTable;
    for (itTable = table.begin(); itTable != table.end(); ++itTable) {
        std::ostringstream oss;
        oss << "| " << itTable->first << " ";
        for (std::size_t i = 0; i < M; ++i)
            oss << "| " << std::fixed << std::setprecision(2)
                << (*itTable->second.first)[i] << " ";
        oss << "| ";
        for (std::size_t i = 0; i < M; ++i)
            oss << "| " << (*itTable->second.second)[i] << " ";
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

    std::vector<std::string>::const_iterator itRows;
    for (itRows = rows.begin(); itRows != rows.end(); ++itRows)
        fout << *itRows << "\n";

    fout.close();
    return 0;
}