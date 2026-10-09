#include <iostream>
#include "average.h"
#include "mode_average.h"

int main() {
    std::cout << "ordinary::average(3, 4)     = "
              << ordinary::average(3, 4) << '\n';

    std::cout << "modified::mode_average(3,4) = "
              << modified::mode_average(3, 4) << '\n';

    return 0;
}