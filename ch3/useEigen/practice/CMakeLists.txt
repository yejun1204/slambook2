cmake_minimum_required(VERSION 2.8)
project(useEigen)

SET ( CMAKE_BUILD_TYPE Debug )
SET ( CMAKE_C_COMPILER "g++" )

#SET ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_TYPE} )
#include_directories("/usr/include/eigen3")
find_package(Eigen3)
add_executable(eigenMatrix eigenMatrix.cpp)
target_link_libraries(eigenMatrix Eigen3::Eigen)

