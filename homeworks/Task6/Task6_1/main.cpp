#include "robot.h"
#include <vector>

int main() {
    QuadrupedRobot a;
    QuadrupedRobot b("R1", "Spot", 5.0, std::vector<double>(10, 1.0));
    QuadrupedRobot c(b);
    a = b;
    return 0;
}