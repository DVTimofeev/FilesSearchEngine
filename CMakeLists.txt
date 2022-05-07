cmake_minimum_required(VERSION 3.16)
project(grad_work)

set(CMAKE_CXX_STANDARD 17)

# gtest block start
include(FetchContent)
FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
# gtest block end

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(MY_INCLUDE_DIR 
    ${CMAKE_SOURCE_DIR}/include
)

set(MY_SRC_DIR
    ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(src)
add_subdirectory(tests)
