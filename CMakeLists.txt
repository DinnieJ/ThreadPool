CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(threadpoolremake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PROGRAM_PATH "/mingw64/bin/make.exe")
set(CMAKE_BUILD_TYPE Debug)

include_directories("${PROJECT_SOURCE_DIR}")

find_package(Threads)

add_executable(
    threadpoolremake
    ThreadPool.hpp
    ThreadPool.cpp
    main.cpp
)