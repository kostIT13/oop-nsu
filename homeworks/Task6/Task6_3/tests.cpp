#include <gtest/gtest.h>
#include "robot.h"
#include <stdexcept>

static double make10(double v) { return v; }

TEST(QuadrupedRobotTest, DefaultConstructor) {
    QuadrupedRobot r;
    EXPECT_EQ(r.getId(), "R0");
    EXPECT_EQ(r.getName(), "Unnamed");
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 100.0);
    EXPECT_EQ(r.getCurrentCommand(), "idle");
    EXPECT_DOUBLE_EQ(r.getTodayDistance(), 0.0);
    ASSERT_NE(r.getLast10(), nullptr);
    for (int i = 0; i < QuadrupedRobot::getDays(); ++i)
        EXPECT_DOUBLE_EQ(r.getLast10()[i], 0.0);
}

TEST(QuadrupedRobotTest, InitConstructor) {
    double arr[10] = {1,2,3,4,5,6,7,8,9,10};
    QuadrupedRobot r("R1", "Spot", 55.0, "walk", 5.0, arr);
    EXPECT_EQ(r.getId(), "R1");
    EXPECT_EQ(r.getName(), "Spot");
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 55.0);
    EXPECT_EQ(r.getCurrentCommand(), "walk");
    EXPECT_DOUBLE_EQ(r.getTodayDistance(), 5.0);
    for (int i = 0; i < 10; ++i)
        EXPECT_DOUBLE_EQ(r.getLast10()[i], arr[i]);
}

TEST(QuadrupedRobotTest, InitConstructorEmptyIdThrows) {
    double arr[10] = {0};
    EXPECT_THROW(
        QuadrupedRobot("", "Spot", 50.0, "walk", 1.0, arr),
        std::invalid_argument);
}

TEST(QuadrupedRobotTest, InitConstructorNullArray) {
    QuadrupedRobot r("R9", "Bot", 50.0, "walk", 1.0, nullptr);
    for (int i = 0; i < 10; ++i)
        EXPECT_DOUBLE_EQ(r.getLast10()[i], 0.0);
}

TEST(QuadrupedRobotTest, Normalization) {
    double bad[10] = {-1,-2,3,4,-5,6,7,-8,9,10};
    QuadrupedRobot r("R2", "", -50.0, "stand", -3.0, bad);
    EXPECT_EQ(r.getName(), "Unnamed");
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 0.0);
    EXPECT_DOUBLE_EQ(r.getTodayDistance(), 0.0);
    for (int i = 0; i < 10; ++i)
        EXPECT_GE(r.getLast10()[i], 0.0);
}

TEST(QuadrupedRobotTest, NormalizationBatteryUpper) {
    double arr[10] = {0};
    QuadrupedRobot r("R3", "Bot", 250.0, "run", 0.0, arr);
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 100.0);
}

TEST(QuadrupedRobotTest, CopyConstructorDeepCopy) {
    double arr[10] = {1,2,3,4,5,6,7,8,9,10};
    QuadrupedRobot a("R4", "Spot", 30.0, "walk", 7.0, arr);
    QuadrupedRobot b(a);
    EXPECT_EQ(b.getId(), a.getId());
    EXPECT_EQ(b.getName(), a.getName());
    EXPECT_DOUBLE_EQ(b.getBatteryLevel(), a.getBatteryLevel());
    for (int i = 0; i < 10; ++i)
        EXPECT_DOUBLE_EQ(b.getLast10()[i], a.getLast10()[i]);
    // глубокое копирование: разные указатели
    EXPECT_NE(a.getLast10(), b.getLast10());
}

TEST(QuadrupedRobotTest, AssignmentOperatorDeepCopy) {
    double arr[10] = {1,2,3,4,5,6,7,8,9,10};
    QuadrupedRobot a;
    QuadrupedRobot b("R5", "Spot", 42.0, "run", 9.0, arr);
    a = b;
    EXPECT_EQ(a.getId(), b.getId());
    EXPECT_EQ(a.getName(), b.getName());
    EXPECT_DOUBLE_EQ(a.getBatteryLevel(), b.getBatteryLevel());
    for (int i = 0; i < 10; ++i)
        EXPECT_DOUBLE_EQ(a.getLast10()[i], b.getLast10()[i]);
    EXPECT_NE(a.getLast10(), b.getLast10());
}

TEST(QuadrupedRobotTest, SelfAssignment) {
    double arr[10] = {1,2,3,4,5,6,7,8,9,10};
    QuadrupedRobot a("R6", "Spot", 20.0, "walk", 1.0, arr);
    const double* before = a.getLast10();
    a = a;
    EXPECT_EQ(a.getId(), "R6");
    EXPECT_EQ(a.getLast10(), before);  // тот же буфер
}

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

    double bad[10] = {-1,-2,-3,-4,-5,-6,-7,-8,-9,-10};
    r.setLast10(bad);
    for (int i = 0; i < 10; ++i)
        EXPECT_DOUBLE_EQ(r.getLast10()[i], 0.0);

    double good[10] = {1,2,3,4,5,6,7,8,9,10};
    r.setLast10(good);
    for (int i = 0; i < 10; ++i)
        EXPECT_DOUBLE_EQ(r.getLast10()[i], good[i]);
}

TEST(QuadrupedRobotTest, Getters) {
    double arr[10] = {1,2,3,4,5,6,7,8,9,10};
    QuadrupedRobot r("R7", "Spot", 77.0, "walk", 4.0, arr);
    EXPECT_EQ(r.getId(), "R7");
    EXPECT_EQ(r.getName(), "Spot");
    EXPECT_DOUBLE_EQ(r.getBatteryLevel(), 77.0);
    EXPECT_EQ(r.getCurrentCommand(), "walk");
    EXPECT_DOUBLE_EQ(r.getTodayDistance(), 4.0);
    EXPECT_EQ(QuadrupedRobot::getDays(), 10);
}