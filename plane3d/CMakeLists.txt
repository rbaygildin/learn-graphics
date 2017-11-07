cmake_minimum_required(VERSION 3.8)
project(plane3d)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_PREFIX_PATH "/Applications/Qt/5.9.2/clang_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCE_FILES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        figures/cube.h
        figures/cube.cpp
        figures/figure.h
        figures/icosahedron.h
        figures/icosahedron.cpp
        figures/octahedron.h
        figures/octahedron.cpp
        figures/pyramid.h
        figures/pyramid.cpp
        affine.h
        affine.cpp
        affine/affine.cpp affine/affine.h figures/figure.cpp)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

find_package(Armadillo REQUIRED)    # this is where the error occurs
include_directories(${ARMADILLO_INCLUDE_DIRS})

add_executable(plane3d ${SOURCE_FILES})
target_link_libraries(plane3d Qt5::Core Qt5::Widgets ${Boost_Libraries} ${ARMADILLO_LIBRARIES})