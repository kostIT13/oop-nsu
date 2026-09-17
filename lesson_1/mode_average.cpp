#include "mode_average.h"
#include "average.h"
#include <random>

namespace ModeAverage {
	int mode_average(const int& a, const int& b) {
		static std::mt19937 gen(std::random_device{}());

		int result = (a + b) / 2;

		if (std::bernoulli_distribution(0.5)(gen))
			result += std::uniform_int_distribution<int>(-10, 10)(gen);
		return result;
	}
	double mode_average(const double &a, const double &b) {
		static std::mt19937 gen(std::random_device{}());

		double result = (a + b) / 2.0;

		if (std::bernoulli_distribution(0.5)(gen))
			result += std::uniform_int_distribution<int>(-10, 10)(gen);
		return result;
	}
}	
