// Copyright 2016 - Roman Yarnykh. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <glm/vec3.hpp>
#include "Window.h"
#include "figures/Torus.h"
#include "figures/Sphere.h"
#include "figures/Teapot.h"
#include "figures/WireTorus.h"
#include "figures/Dodecahedron.h"

#define SHADER_PROGRAM(SHADER_NAME, SHADER_PROGRAM) new Shader("data/shaders((SHADER_NAME)).vert", "data/shaders((SHADER_NAME)).frag", SHADER_PROGRAM)

/**
 * Initialize window context, add figures
 */
Window::Window() {
    if (!glfwInit()) {
        BOOST_LOG_TRIVIAL(fatal) << "Could not to initialize GLFW context";
        exit(EXIT_FAILURE);
    }
    BOOST_LOG_TRIVIAL(info) << "GLFW context loaded successfully";

    wnd = glfwCreateWindow(640, 480, "OpenGL start", nullptr, nullptr);
    if (!wnd) {
        BOOST_LOG_TRIVIAL(fatal) << "Window could not created";
        glfwDestroyWindow(wnd);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    BOOST_LOG_TRIVIAL(info) << "Window created successfully";
    glfwMakeContextCurrent(wnd);
    GLenum err = glewInit();
    if (err != GL_FALSE)
        exit(EXIT_FAILURE);
    glfwSetKeyCallback(wnd, Window::keyCallback);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    createBuffers();
    loadShaders();
    figures.emplace_back(new Torus(36, 36, 0.7, 0.1));
    figures.emplace_back(new Cube());
    figures.emplace_back(new NoelTree());
    figures.emplace_back(new Sphere(0.3f));
    figures.emplace_back(new Teapot());
    figures.emplace_back(new WireTorus(0.2, 0.09));
    initLighting();
}

/**
 * Destruct context
 */
Window::~Window() {
    for (auto &figure : figures)
        delete figure;
    deleteBuffers();
    deleteShaders();
    glfwDestroyWindow(wnd);
    glfwTerminate();
    BOOST_LOG_TRIVIAL(info) << "GLFW terminated. Bye!";
}

/**
 * Handle key events
 * @param window
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        exit(EXIT_SUCCESS);

}

/**
 * Run main loop, draw figures
 */
void Window::run() {
    BOOST_LOG_TRIVIAL(info) << "Render content";

    while (!glfwWindowShouldClose(wnd)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(DARK_GRAY, 1);
        float ratio;
        int width, height;
        glfwGetFramebufferSize(wnd, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(145, ratio, 10.0f, 0.0f);
        for (auto &figure : figures)
            figure->draw();
        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }
}

void Window::createBuffers() {

}

void Window::deleteBuffers() {

}

/**
 * Load shaders from file
 */
void Window::loadShaders() {
    program = glCreateProgram();
    shader = SHADER_PROGRAM("shader", program);
    lightShader = SHADER_PROGRAM("lighting", program);
    glLinkProgram(program);
    glUseProgram(program);
}

/**
 * Delete shaders
 */
void Window::deleteShaders() {
    BOOST_LOG_TRIVIAL(info) << "Shaders deleted";
    if (!shader)
        delete shader;
    if (!lightShader)
        delete lightShader;
}

/**
 * Create light source
 */
void Window::initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = {0.3,0.3,0.3,1};
    GLfloat diffuseLight[] = {1,1,1,1};
    GLfloat specularLight[] = {1,1,1,1};
    GLfloat position[] = {0.2f, 0.6f, 0.2f, 4.0f};

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.2);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.4);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);

    glFrontFace(GL_CCW);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}
