#pragma once
#include <string>
#include <vector>

class QuadrupedRobot {
private:
    const std::string id;
    std::string name;
    double todayDistance;
    std::vector<double> last10;

    static void check(const std::string& id, const std::string& name,
                      double d, const std::vector<double>& v);

public:
    QuadrupedRobot();
    QuadrupedRobot(const std::string& id, const std::string& name,
                   double dist, const std::vector<double>& last10);
    QuadrupedRobot(const QuadrupedRobot& o);
    QuadrupedRobot& operator=(const QuadrupedRobot& o);
};