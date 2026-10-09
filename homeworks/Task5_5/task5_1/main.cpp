#include <iostream>
#include "average.h"
#include "mode_average.h"

int main() {
    std::cout << "ordinary::average(3, 4)     = "
              << ordinary::average(3, 4) << '\n';

    std::cout << "modified::mode_average(3,4) = "
              << modified::mode_average(3, 4) << '\n';

    std::cout << "10 tests mode_average(100,100): ";
    for (int i = 0; i < 10; ++i)
        std::cout << modified::mode_average(100, 100) << ' ';
    std::cout << '\n';

    return 0;
}