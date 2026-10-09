# Библиотека ordinary
add_library(ordinary_lib STATIC average.cpp)
target_include_directories(ordinary_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Библиотека modified
add_library(modified_lib STATIC mode_average.cpp)
target_include_directories(modified_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})