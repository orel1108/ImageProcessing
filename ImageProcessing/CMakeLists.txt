cmake_minimum_required(VERSION 3.8)

project(ImageProcessing)
 
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

add_definitions(-D_USE_MATH_DEFINES)
 
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(INCLUDE_DIR
    include/Common/Matrix.h
    include/IO/ImageIO.h
    include/Operations/IImageOperationBase.h
    include/Operations/ImageOperationBoxFilter.h
    include/Operations/ImageOperationCircularFilter.h
    include/Operations/ImageOperationGaussianFilter.h
    include/Operations/ImageOperationGrayScale.h
    include/Operations/ImageOperationInvertPixels.h
    include/Operations/ImageOperationLinearFilter.h
    include/Wrappers/QImageWrapper.h
    include/BoxFilterWidget.h
    include/ImageProcessing.h)

set(SOURCE_FILES main.cpp
    src/IO/ImageIO.cpp
    src/Wrappers/QImageWrapper.cpp
    src/BoxFilterWidget.cpp
    src/ImageProcessing.cpp)

add_executable(${PROJECT_NAME} ${INCLUDE_DIR} ${SOURCE_FILES})
 
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
