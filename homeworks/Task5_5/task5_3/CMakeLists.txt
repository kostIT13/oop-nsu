cmake_minimum_required(VERSION 3.16)
project(oop_hw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Подключаем googletest через FetchContent ---
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

# Для Windows: чтобы gtest не перезаписывал настройки компилятора
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# --- Библиотека в поддиректории ---
add_subdirectory(lib)

# --- Основное приложение ---
add_executable(app main.cpp)
target_link_libraries(app PRIVATE ordinary_lib modified_lib)

# --- Тесты ---
enable_testing()          # ОБЯЗАТЕЛЬНО в корне, иначе ctest не увидит тесты [citation:6]
add_subdirectory(tests)