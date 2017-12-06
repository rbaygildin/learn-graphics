cmake_minimum_required(VERSION 3.8)
project(opengl2)

set(CMAKE_CXX_STANDARD 11)

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

include_directories(/usr/local/Cellar/freeimage/3.17.0_1/include/)

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
        shader/shaders.h shader/shaders.cpp
        static_geometry.h static_geometry.cpp
        vertexBufferObject.h vertexBufferObject.cpp
        texture.h texture.cpp
        skybox.h skybox.cpp
        dirLight.h dirLight.cpp
        flyingCamera.h flyingCamera.cpp
#        renderScene.cpp
        main.cpp
        common.h
        App.cpp App.h Logger.cpp logger.cpp logger.h)

add_executable(opengl2 ${SOURCE_FILES})


target_link_libraries(
        opengl2
        glfw
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${Boost_LIBRARIES}
        ${FREEIMAGE_LIBRARIES}
        ${EXTRA_LIBS}
        /usr/local/Cellar/freeimage/3.17.0_1/lib/libfreeimage.dylib
)