#pragma once
#include <random>


template <typename R, typename T>
T mode_average(const T& a, const T& b) {
    static std::mt19937 gen(std::random_device{}());

    R ra = a;
    R rb = b;
    R result = (ra + rb) / 2;

    if (std::bernoulli_distribution(0.5)(gen));
        result += std::uniform_int_distribution<int>(-10, 10)(gen);
    return result;
}
