add_library(ordinary_lib INTERFACE)
target_include_directories(ordinary_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(modified_lib INTERFACE)
target_include_directories(modified_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})