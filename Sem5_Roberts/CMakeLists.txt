cmake_minimum_required(VERSION 3.8)
project(Sem5_Roberts)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_PREFIX_PATH "/Applications/Qt/5.9.2/clang_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(SOURCE_FILES main.cpp figures/cube.h figures/cube.cpp mainwindow.h mainwindow.cpp affine.cpp affine.h figures/figure.h figures/pyramid.cpp figures/pyramid.h figures/octahedron.cpp figures/octahedron.h figures/icosahedron.cpp figures/icosahedron.h)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

add_executable(Sem5_Roberts ${SOURCE_FILES})
target_link_libraries(Sem5_Roberts Qt5::Core Qt5::Widgets ${Boost_Libraries})