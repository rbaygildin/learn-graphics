cmake_minimum_required(VERSION 3.8)
project(opengl_start)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE 1)


# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_library(COCOA_LIBRARY Cocoa)
find_library(OpenGL_LIBRARY OpenGL)
find_library(IOKIT_LIBRARY IOKit)
find_library(COREVIDEO_LIBRARY CoreVideo)
SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})

set(SOURCE_FILES
        main.cpp
        shader.frag
        shader.vert)

add_executable(opengl_start ${SOURCE_FILES})

target_link_libraries(
        opengl_start
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${EXTRA_LIBS}
)