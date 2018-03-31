cmake_minimum_required(VERSION 3.8)

project(ImageProcessing)
 
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

add_definitions(-D_USE_MATH_DEFINES)
 
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

#include_directories(${CMAKE_SOURCE_DIR}/include)

#set(INCLUDE_DIR
#    include/Common/Matrix.h
#    )

set(SOURCE_FILES main.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
 
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
