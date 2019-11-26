cmake_minimum_required(VERSION 2.8)
#set(CMAKE_CXX_COMPILER:FILEPATH /usr/bin/g++)
project(imageBasics)

#find_package(OpenCV REQUIRED)
#MESSAGE(${OpenCV_INCLUDE_DIRS})
#include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(imageBasics imageBasics.cpp)
# 链接OpenCV库
target_link_libraries(imageBasics ${OpenCV_LIBS})

add_executable(undistortImage undistortImage.cpp)
# 链接OpenCV库
target_link_libraries(undistortImage ${OpenCV_LIBS})
