cmake_minimum_required(VERSION 3.8)
project(bezier)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_PREFIX_PATH "/Applications/Qt/5.9.2/clang_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

set(SOURCE_FILES
        bezier.pro
        bezier.pro.user
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui curves/Bezier.cpp curves/Bezier.h curves/Curve.cpp curves/Curve.h curves/CompositeBezier.cpp curves/CompositeBezier.h)

add_executable(bezier ${SOURCE_FILES})

target_link_libraries(bezier Qt5::Core Qt5::Widgets ${Boost_Libraries})