cmake_minimum_required(VERSION 3.16)

set(this gtests_test)

set(Sources
    example_test.cpp
    test_ConvertJSON.cpp
    test_InvertedIndex.cpp
    test_SearchEngine.cpp
)

set(Testing_cpp
        ${MY_SRC_DIR}/ConvertJSON.cpp
        ${MY_SRC_DIR}/InvertedIndex.cpp
        ${MY_SRC_DIR}/SearchEngine.cpp
)

add_executable(${this} ${Sources} ${Testing_cpp})

target_link_libraries(${this} PUBLIC
    gtest_main
)

include(GoogleTest)

target_include_directories(${this} PUBLIC ${MY_INCLUDE_DIR})

gtest_discover_tests(${this})