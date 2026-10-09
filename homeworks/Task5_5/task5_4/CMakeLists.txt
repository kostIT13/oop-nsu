cmake_minimum_required(VERSION 3.16)
project(oop_hw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================
# ОПЦИЯ: включать/выключать сборку тестов
# ON  (по умолчанию) — тесты собираются
# OFF                — тесты не собираются, googletest не скачивается
# ============================================================
option(BUILD_TESTS "Build unit tests with GoogleTest" ON)

# --- Библиотека в поддиректории (нужна всегда) ---
add_subdirectory(lib)

# --- Основное приложение (нужно всегда) ---
add_executable(app main.cpp)
target_link_libraries(app PRIVATE ordinary_lib modified_lib)

# --- Тесты (только если BUILD_TESTS=ON) ---
if(BUILD_TESTS)
    message(STATUS "Tests: ENABLED — подключаю googletest и tests/")

    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )

    # Для Windows: чтобы gtest не перезаписывал настройки компилятора
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)

    enable_testing()          # нужно только когда тесты включены
    add_subdirectory(tests)
else()
    message(STATUS "Tests: DISABLED — googletest и tests/ не подключаются")
endif()