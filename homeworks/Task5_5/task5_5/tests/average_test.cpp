#include <gtest/gtest.h>
#include "average.h"

// --- int ---
TEST(AverageIntTest, PositiveNumbers) {
    EXPECT_EQ(ordinary::average<int>(10, 20), 15);
}

TEST(AverageIntTest, IntegerDivisionTruncates) {
    EXPECT_EQ(ordinary::average<int>(3, 4), 3);   // (3+4)/2 = 3
}

TEST(AverageIntTest, NegativeNumbers) {
    EXPECT_EQ(ordinary::average<int>(-10, -20), -15);
}

// --- double ---
TEST(AverageDoubleTest, KeepsFraction) {
    EXPECT_DOUBLE_EQ(ordinary::average<double>(3.0, 4.0), 3.5);
}

TEST(AverageDoubleTest, NegativeValues) {
    EXPECT_DOUBLE_EQ(ordinary::average<double>(-3.0, 4.0), 0.5);
}

// --- long long ---
TEST(AverageLongTest, BigValues) {
    EXPECT_EQ(ordinary::average<long long>(1'000'000'000LL, 3'000'000'000LL),
              2'000'000'000LL);
}

// --- Демонстрация EXPECT_ vs ASSERT_ ---
TEST(AverageTest, ExpectContinuesAfterFailure) {
    EXPECT_EQ(ordinary::average<int>(3, 4), 3);
    EXPECT_EQ(ordinary::average<int>(5, 5), 99);   // ПРОВАЛ
    EXPECT_EQ(ordinary::average<int>(0, 0), 0);    // всё равно выполнится
}

TEST(AverageTest, AssertStopsAfterFailure) {
    ASSERT_EQ(ordinary::average<int>(5, 5), 99);   // ПРОВАЛ — дальше не пойдёт
    EXPECT_EQ(ordinary::average<int>(0, 0), 0);
}