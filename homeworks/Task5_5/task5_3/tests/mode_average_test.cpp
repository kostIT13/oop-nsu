#include <gtest/gtest.h>
#include "mode_average.h"

// mode_average добавляет шум с вероятностью 50%, поэтому
// точное значение предсказать нельзя. Проверяем границы.

TEST(ModeAverageTest, WithinExpectedBounds) {
    // Без шума результат = (a+b)/2.
    // С шумом: (a+b)/2 + [-10, 10].
    for (int i = 0; i < 100; ++i) {
        int result = modified::mode_average(100, 100);
        EXPECT_GE(result, 90);   // >= 100 - 10
        EXPECT_LE(result, 110);  // <= 100 + 10
    }
}

TEST(ModeAverageTest, ZeroInputGivesSmallRange) {
    // (0+0)/2 = 0, шум [-10, 10] → результат в [-10, 10]
    for (int i = 0; i < 50; ++i) {
        int result = modified::mode_average(0, 0);
        EXPECT_GE(result, -10);
        EXPECT_LE(result, 10);
    }
}

// ПРОВАЛЬНЫЙ тест: mode_average часто НЕ равен точному среднему
TEST(ModeAverageTest, SometimesDeviatesFromExactAverage) {
    bool deviated = false;
    for (int i = 0; i < 100; ++i) {
        if (modified::mode_average(100, 100) != 100) {
            deviated = true;
            break;
        }
    }
    // Этот тест ПРОВАЛИТСЯ, если шум ни разу не сработает,
    // но на практике он с высокой вероятностью пройдёт.
    EXPECT_TRUE(deviated);
}