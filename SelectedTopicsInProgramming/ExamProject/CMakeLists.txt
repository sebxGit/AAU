cmake_minimum_required(VERSION 3.0)
project(ExamProject)

set(CMAKE_CXX_STANDARD 23)

add_executable(ExamProject main.cpp)
add_executable(ExamProjectTest unitTests.cpp)
add_executable(ExamProjectBenchmark main_bm.cpp)
