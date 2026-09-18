#include <iostream>
#include "average.h"
#include "mode_average.h"

int main() {
    
    int a, b;
    std::cin >> a;
    std::cin >> b;

    std::cout << res_average<int, double>(a,b) << '\n';
    std::cout << res_mode_average<int, double>(a,b);
    
    return 0;
}