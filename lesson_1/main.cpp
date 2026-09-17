#include <iostream>
#include "average.h"
#include "mode_average.h"
#include "mode_average_params.h"

namespace Average {
	std:: int average(const int a, const int b);
}

int main() {
	int a, b;
	std::cin >> a;
	std::cin >> b;

	std::cout << average(a, b) << '\n';
	std::cout << mode_average(a, b);
	std::cout << mode_average_params(a, b);

	return 0;
}