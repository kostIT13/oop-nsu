#include "average.h"

namespace Average {
	int average(int a, int b) {
		int sum = a + b;
		return sum / 2;
	}
	double average(double a, double b) {
		double sum = a + b;
		return sum / 2.0;
	}
}