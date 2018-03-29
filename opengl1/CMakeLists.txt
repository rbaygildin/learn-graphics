cmake_minimum_required(VERSION 3.8)
project(opengl1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE 1)


# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# opengl
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})

# glm
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_library(COCOA_LIBRARY Cocoa)
find_library(OpenGL_LIBRARY OpenGL)
find_library(IOKIT_LIBRARY IOKit)
find_library(COREVIDEO_LIBRARY CoreVideo)
SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})

set(BOOST_COMPONENTS
        unit_test_framework
        program_options
        log
        log_setup
        system
        thread) # And other components you need

set(Boost_USE_STATIC_LIBS ON) # Easier to deploy elsewhere
set(BOOST_ROOT /usr/local/opt/boost) # Useful for boost from brew
set(BOOST_LIBRARYDIR /usr/local/opt/boost/lib64)
find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})

include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES
        main.cpp
        data/shaders/shader.vert
        data/shaders/shader.frag
        data/shaders/texture.vert
        data/shaders/texture.frag
        data/shaders/lighting.frag
        data/shaders/lighting.vert
        figures/NoelTree.cpp figures/NoelTree.h figures/Figure.cpp figures/Figure.h shaders/Shader.cpp shaders/Shader.h Window.cpp Window.h figures/Cube.cpp figures/Cube.h common.h figures/Torus.cpp figures/Torus.h figures/Sphere.cpp figures/Sphere.h figures/Teapot.cpp figures/Teapot.h figures/WireTorus.cpp figures/WireTorus.h figures/Dodecahedron.cpp figures/Dodecahedron.h)

add_executable(opengl1 ${SOURCE_FILES})

add_custom_command(TARGET opengl1 POST_BUILD
        COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
        )

target_link_libraries(
        opengl1
        glfw
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${Boost_LIBRARIES}
        ${EXTRA_LIBS}
)