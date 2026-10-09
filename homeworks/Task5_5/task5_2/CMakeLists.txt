cmake_minimum_required(VERSION 3.16)
project(oop_hw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем поддиректорию с библиотекой
add_subdirectory(lib)

# Исполняемый файл из main.cpp (в корне)
add_executable(app main.cpp)

# Линкуем с библиотеками из lib/
target_link_libraries(app PRIVATE ordinary_lib modified_lib)