#pragma once

template <typename R, typename T>
R average(T a, T b) {
    R ra = a;
    R rb = b;
    return (ra + rb) / 2;
}