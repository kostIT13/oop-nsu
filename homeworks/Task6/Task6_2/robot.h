#pragma once
#include <string>
#include <vector>

class QuadrupedRobot {
private:
    const std::string id;          // уникальный, неизменяемый
    std::string name;              // непустое
    double batteryLevel;           // 0..100
    std::string currentCommand;    // текущая команда
    double todayDistance;          // >= 0
    std::vector<double> last10;    // последние 10 дней, >= 0

    // Нормализация: приводит поля в рабочий диапазон
    static std::string normalizeName(const std::string& n);
    static double normalizeBattery(double b);
    static double normalizeDistance(double d);
    static std::vector<double> normalizeLast10(const std::vector<double>& v);

    // Проверка "жёстких" инвариантов (id)
    static void checkId(const std::string& id);

public:
    QuadrupedRobot();
    QuadrupedRobot(const std::string& id, const std::string& name,
                   double battery, const std::string& command,
                   double dist, const std::vector<double>& last10);
    QuadrupedRobot(const QuadrupedRobot& o);
    QuadrupedRobot& operator=(const QuadrupedRobot& o);

    // Геттеры
    const std::string& getId() const;
    const std::string& getName() const;
    double getBatteryLevel() const;
    const std::string& getCurrentCommand() const;
    double getTodayDistance() const;
    const std::vector<double>& getLast10() const;

    // Сеттеры (id — неизменяемый, сеттера нет)
    void setName(const std::string& n);
    void setBatteryLevel(double b);
    void setCurrentCommand(const std::string& c);
    void setTodayDistance(double d);
    void setLast10(const std::vector<double>& v);
};