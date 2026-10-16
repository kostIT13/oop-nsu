add_executable(lib_tests # создаем исполняемый файл
    average_test.cpp
    mode_average_test.cpp
)

target_link_libraries(lib_tests # линкуем
    PRIVATE
        ordinary_lib
        modified_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lib_tests) # регистрирует каждый тест