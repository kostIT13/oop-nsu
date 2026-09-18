#include "mode_average.h"
#include "average.h"
#include <random>


template <typename T>
T mode_average(const T& a, const T& b) {
    static std::mt19937 gen(std::random_device{}());

    T result = (a + b) / 2;

    if (std::bernoulli_distribution(0.5)(gen))
        result += std::uniform_int_distribution<int>(-10, 10)(gen);
    return result;
}
