#pragma once

template <typename T, int p = 2>
T average(T a, T b) {
    T sum = a + b;
    return sum / 2;
}