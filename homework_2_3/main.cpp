#include <iostream>
#include "average.h"
#include "mode_average.h"

int main() {
    
    int a, b;
    std::cin >> a;
    std::cin >> b;

    int res_average = average(a,b);
    int res_mode_average = mode_average(a,b);

    std::cout << res_average << '\n';
    std::cout << res_mode_average;
    
    return 0;
}