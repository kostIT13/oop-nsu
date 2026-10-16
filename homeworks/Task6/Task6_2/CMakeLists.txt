cmake_minimum_required(VERSION 3.14)
project(QuadrupedRobot CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основная программа
add_executable(robot main.cpp QuadrupedRobot.cpp)

# Тесты
enable_testing()
find_package(GTest REQUIRED)

add_executable(robot_tests tests.cpp QuadrupedRobot.cpp)
target_link_libraries(robot_tests PRIVATE GTest::gtest GTest::gtest_main)

add_test(NAME robot_tests COMMAND robot_tests)