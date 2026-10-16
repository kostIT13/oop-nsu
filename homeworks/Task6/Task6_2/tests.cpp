#include <gtest/gtest.h>
#include "robot.h"
#include <vector>

// --- default constructor ---
TEST(QuadrupedRobotTest, DefaultConstructor) {
    QuadrupedRobot r;
    EXPECT_EQ(r.getId(), "R0");
    EXPECT_EQ(r.getName(), "Unnamed");
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 100.0);
    EXPECT_EQ(r.getCurrentCommand(), "idle");
    EXPECT_DOUBLE_EQ(r.getTodayDistance(), 0.0);
    EXPECT_EQ(r.getLast10().size(), 10u);
}

// --- initialization constructor ---
TEST(QuadrupedRobotTest, InitConstructor) {
    QuadrupedRobot r("R1", "Spot", 55.0, "walk", 5.0,
                     std::vector<double>(10, 1.0));
    EXPECT_EQ(r.getId(), "R1");
    EXPECT_EQ(r.getName(), "Spot");
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 55.0);
    EXPECT_EQ(r.getCurrentCommand(), "walk");
    EXPECT_DOUBLE_EQ(r.getTodayDistance(), 5.0);
}

TEST(QuadrupedRobotTest, InitConstructorEmptyIdThrows) {
    EXPECT_THROW(
        QuadrupedRobot("", "Spot", 50.0, "walk", 1.0, std::vector<double>(10, 0.0)),
        std::invalid_argument);
}

// --- нормализация ---
TEST(QuadrupedRobotTest, Normalization) {
    QuadrupedRobot r("R2", "", -50.0, "stand", -3.0,
                     std::vector<double>({-1.0, 2.0, -3.0, 4.0}));
    EXPECT_EQ(r.getName(), "Unnamed");            // пустое имя -> "Unnamed"
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 0.0);   // -50 -> 0
    EXPECT_DOUBLE_EQ(r.getTodayDistance(), 0.0);  // -3 -> 0
    EXPECT_EQ(r.getLast10().size(), 10u);         // дополнили до 10
    for (double x : r.getLast10()) EXPECT_GE(x, 0.0);
}

TEST(QuadrupedRobotTest, NormalizationBatteryUpper) {
    QuadrupedRobot r("R3", "Bot", 250.0, "run", 0.0, std::vector<double>(10, 0.0));
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 100.0); // 250 -> 100
}

// --- copy constructor ---
TEST(QuadrupedRobotTest, CopyConstructor) {
    QuadrupedRobot a("R4", "Spot", 30.0, "walk", 7.0, std::vector<double>(10, 2.0));
    QuadrupedRobot b(a);   // copy ctor
    EXPECT_EQ(b.getId(), a.getId());
    EXPECT_EQ(b.getName(), a.getName());
    EXPECT_DOUBLE_EQ(b.getBatteryLevel(), a.getBatteryLevel());
    EXPECT_DOUBLE_EQ(b.getTodayDistance(), a.getTodayDistance());
    EXPECT_EQ(b.getLast10(), a.getLast10());
}

// --- assignment operator ---
TEST(QuadrupedRobotTest, AssignmentOperator) {
    QuadrupedRobot a;
    QuadrupedRobot b("R5", "Spot", 42.0, "run", 9.0, std::vector<double>(10, 3.0));
    a = b;
    EXPECT_EQ(a.getId(), b.getId());
    EXPECT_EQ(a.getName(), b.getName());
    EXPECT_DOUBLE_EQ(a.getBatteryLevel(), b.getBatteryLevel());
    EXPECT_DOUBLE_EQ(a.getTodayDistance(), b.getTodayDistance());
    EXPECT_EQ(a.getLast10(), b.getLast10());
}

TEST(QuadrupedRobotTest, SelfAssignment) {
    QuadrupedRobot a("R6", "Spot", 20.0, "walk", 1.0, std::vector<double>(10, 0.5));
    a = a;  // не должно падать
    EXPECT_EQ(a.getId(), "R6");
}

// --- сеттеры ---
TEST(QuadrupedRobotTest, SettersNormalize) {
    QuadrupedRobot r;
    r.setName("");
    EXPECT_EQ(r.getName(), "Unnamed");
    r.setBatteryLevel(-10.0);
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 0.0);
    r.setBatteryLevel(200.0);
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 100.0);
    r.setTodayDistance(-5.0);
    EXPECT_DOUBLE_EQ(r.getTodayDistance(), 0.0);
    r.setCurrentCommand("jump");
    EXPECT_EQ(r.getCurrentCommand(), "jump");
    r.setLast10(std::vector<double>({-1.0, -2.0}));
    EXPECT_EQ(r.getLast10().size(), 10u);
    for (double x : r.getLast10()) EXPECT_GE(x, 0.0);
}

// --- геттеры ---
TEST(QuadrupedRobotTest, Getters) {
    QuadrupedRobot r("R7", "Spot", 77.0, "walk", 4.0, std::vector<double>(10, 1.0));
    EXPECT_EQ(r.getId(), "R7");
    EXPECT_EQ(r.getName(), "Spot");
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 77.0);
    EXPECT_EQ(r.getCurrentCommand(), "walk");
    EXPECT_DOUBLE_EQ(r.getTodayDistance(), 4.0);
    EXPECT_EQ(r.getLast10().size(), 10u);
}