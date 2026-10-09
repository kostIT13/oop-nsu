#pragma once

namespace ordinary {

    template <typename T>
    T average(T a, T b) {
        return (a + b) / static_cast<T>(2);
    }

}