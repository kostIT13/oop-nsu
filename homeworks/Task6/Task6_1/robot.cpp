#include "robot.h"
#include <iostream>
#include <stdexcept>

void QuadrupedRobot::check(const std::string& id, const std::string& name,
                           double d, const std::vector<double>& v) {
    if (id.empty() || name.empty() || d < 0)
        throw std::invalid_argument("bad args");
    for (double x : v) if (x < 0) throw std::invalid_argument("bad dist");
}

QuadrupedRobot::QuadrupedRobot()
    : id("R0"), name("Unnamed"), todayDistance(0), last10(10, 0) {
    std::cout << "default constructor\n";
}

QuadrupedRobot::QuadrupedRobot(const std::string& id, const std::string& name,
                               double dist, const std::vector<double>& last10)
    : id(id), name(name), todayDistance(dist), last10(last10) {
    check(id, name, dist, last10);
    std::cout << "initialization constructor\n";
}

QuadrupedRobot::QuadrupedRobot(const QuadrupedRobot& o)
    : id(o.id), name(o.name), todayDistance(o.todayDistance), last10(o.last10) {
    std::cout << "copy constructor\n";
}

QuadrupedRobot& QuadrupedRobot::operator=(const QuadrupedRobot& o) {
    std::cout << "assignment operator\n";
    if (this != &o) {
        const_cast<std::string&>(id) = o.id;
        name = o.name;
        todayDistance = o.todayDistance;
        last10 = o.last10;
    }
    return *this;
}