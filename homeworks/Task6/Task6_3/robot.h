#pragma once
#include <string>

class QuadrupedRobot {
private:
    const std::string id;         
    std::string name;             
    double batteryLevel;           // 0..100
    std::string currentCommand;    // текущая команда
    double todayDistance;          // >= 0

    // Динамический массив: дистанция за последние 10 дней (сырой указатель!)
    static const int DAYS = 10;
    double* last10;                // владеемый массив размером DAYS

    static std::string normalizeName(const std::string& n);
    static double normalizeBattery(double b);
    static double normalizeDistance(double d);

    void checkId(const std::string& id) const;

public:
    QuadrupedRobot();
    QuadrupedRobot(const std::string& id, const std::string& name,
                   double battery, const std::string& command,
                   double dist, const double* last10Arr);
    QuadrupedRobot(const QuadrupedRobot& o);
    QuadrupedRobot& operator=(const QuadrupedRobot& o);
    ~QuadrupedRobot();   // очистка памяти

    // геттеры
    const std::string& getId() const;
    const std::string& getName() const;
    double getBatteryLevel() const;
    const std::string& getCurrentCommand() const;
    double getTodayDistance() const;
    const double* getLast10() const;      // указатель на массив
    static int getDays();

    // сеттеры
    void setName(const std::string& n);
    void setBatteryLevel(double b);
    void setCurrentCommand(const std::string& c);
    void setTodayDistance(double d);
    void setLast10(const double* arr);    // копирует DAYS значений
};