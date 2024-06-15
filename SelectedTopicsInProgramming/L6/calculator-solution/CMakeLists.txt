cmake_minimum_required(VERSION 3.15)
project(calculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF) # Stick with statically linked libraries

include(doctest.cmake)
include(sanitizers.cmake)

add_executable(calculator_test calculator_test.cpp)
target_link_libraries(calculator_test PRIVATE doctest_with_main)

add_executable(terms_test terms_test.cpp terms.cpp evaluate.cpp print.cpp)
target_link_libraries(terms_test PRIVATE doctest_with_main)

add_executable(expressions_test expressions_test.cpp expressions.cpp terms.cpp evaluate.cpp print.cpp)
target_link_libraries(expressions_test PRIVATE doctest_with_main)

add_executable(print_test print_test.cpp print.cpp terms.cpp)
target_link_libraries(print_test PRIVATE doctest_with_main)


enable_testing()
add_test(NAME calculator_test COMMAND calculator_test)
add_test(NAME terms_test COMMAND terms_test)
add_test(NAME expressions_test COMMAND expressions_test)
add_test(NAME print_test COMMAND print_test)
