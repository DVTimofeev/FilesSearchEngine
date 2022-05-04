cmake_minimum_required(VERSION 3.16)

set(this SearchEngine)

set(Sources
    main.cpp 
    ConvertJSON.cpp 
    InvertedIndex.cpp 
    SearchEngine.cpp
)


add_executable(${this} ${Sources})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(
    Threads REQUIRED
)

target_link_libraries(${this} Threads::Threads)

target_include_directories(${this} PUBLIC ${MY_INCLUDE_DIR})
