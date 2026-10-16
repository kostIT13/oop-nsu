#include "robot.h"
#include <iostream>

int main() {
    std::cout << "--- 1) default ---\n";
    QuadrupedRobot a;

    std::cout << "\n--- 2) initialization ---\n";
    double arr[10] = {1,2,3,4,5,6,7,8,9,10};
    QuadrupedRobot b("R1", "Spot", 55.0, "walk", 5.0, arr);

    std::cout << "\n--- 3) copy constructor ---\n";
    QuadrupedRobot c(b);              // copy ctor

    std::cout << "\n--- 4) assignment operator ---\n";
    a = b;                            // assignment

    std::cout << "\n--- нормализация ---\n";
    double bad[10] = {-1,-2,3,4,-5,6,7,-8,9,10};
    QuadrupedRobot d("R2", "", -50.0, "stand", -3.0, bad);
    std::cout << "name=" << d.getName()
              << " battery=" << d.getBatteryLevel()
              << " todayDist=" << d.getTodayDistance() << "\n";

    std::cout << "\n--- конец main (деструкторы) ---\n";
    return 0;
}