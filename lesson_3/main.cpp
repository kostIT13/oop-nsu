#include <iostream>
#include "average.h"
#include "mode_average.h"

int main() {

    int a, b;
    std::cin >> a;
    std::cin >> b;

    std::cout << average<double>(a, b) << '\n';
    std::cout << mode_average<double>(a, b);

    return 0;
}