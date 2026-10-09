cmake_minimum_required(VERSION 3.16)
project(oop_hw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Библиотека ordinary: обычная реализация ---
add_library(ordinary_lib STATIC average.cpp)
target_include_directories(ordinary_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# --- Библиотека modified: реализация с рандомом ---
add_library(modified_lib STATIC mode_average.cpp)
target_include_directories(modified_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# --- Исполняемый файл ---
add_executable(app main.cpp)
target_link_libraries(app PRIVATE ordinary_lib modified_lib)