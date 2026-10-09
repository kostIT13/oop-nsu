#include <gtest/gtest.h>
#include "average.h"

// Демонстрация EXPECT_: при провале тест ПРОДОЛЖАЕТ выполняться
TEST(AverageTest, ExpectContinuesAfterFailure) {
    EXPECT_EQ(ordinary::average(3, 4), 3);   // пройдёт
    EXPECT_EQ(ordinary::average(1, 2), 1);   // пройдёт (1+2)/2 = 1
    EXPECT_EQ(ordinary::average(10, 20), 15); // пройдёт
    EXPECT_EQ(ordinary::average(5, 5), 99);  // ПРОВАЛ, но тест идёт дальше
    EXPECT_EQ(ordinary::average(0, 0), 0);   // всё равно выполнится
}

// Демонстрация ASSERT_: при провале тест ПРЕРЫВАЕТСЯ
TEST(AverageTest, AssertStopsAfterFailure) {
    ASSERT_EQ(ordinary::average(5, 5), 99);  // ПРОВАЛ — дальше не пойдёт
    EXPECT_EQ(ordinary::average(0, 0), 0);   // эта строка НЕ выполнится
}

// Корректные тесты
TEST(AverageTest, PositiveNumbers) {
    EXPECT_EQ(ordinary::average(10, 20), 15);
}

TEST(AverageTest, NegativeNumbers) {
    EXPECT_EQ(ordinary::average(-10, -20), -15);
}

TEST(AverageTest, MixedNumbers) {
    EXPECT_EQ(ordinary::average(-5, 5), 0);
}

TEST(AverageTest, ZeroValues) {
    EXPECT_EQ(ordinary::average(0, 0), 0);
}