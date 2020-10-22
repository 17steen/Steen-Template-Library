cmake_minimum_required(VERSION 2.8.6)
project(test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(test0 test.cpp String.cpp)

add_definitions(-D_DEBUG_LOG)
set(CMAKE_CXX_FLAGS  "-std=c++11 ${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
