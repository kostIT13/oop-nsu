#include "mode_average.h"
#include "average.h"
#include <random>

double mode_average(int a, int b) {
	static std::mt19937 gen(std::random_device{}());

	double result = average(a, b);

	if (std::bernoulli_distribution(0.5)(gen))
		result += std::uniform_int_distribution<int>(-10, 10)(gen);
	return result;
}