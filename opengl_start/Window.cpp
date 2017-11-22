//
// Created by Max Heartfield on 22.11.17.
//

#include "Window.h"
#include "shaders/VertexShader.h"
#include "shaders/FragShader.h"
#include "figures/NoelTree.h"

Window::Window() {

    glfwSetErrorCallback(this->error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    wnd = glfwCreateWindow(640, 480, "Simple example", nullptr, nullptr);
    if (!wnd) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(wnd);
    glewInit();
    glfwSetKeyCallback(wnd, this->key_callback);
    createScene();
    loadContext();
}

Window::~Window() {
    glfwDestroyWindow(wnd);
    glfwTerminate();
}

void Window::run() {
    while (!glfwWindowShouldClose(wnd)) {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(wnd, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        for (auto &figure : figures)
            figure->draw();
        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }
}

void Window::error_callback(int error, const char *description) {
    fputs(description, stderr);
}

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void Window::loadContext() {
    //Create program
    program = glCreateProgram();

    //Load shaders
    vertexShader = new VertexShader("lighting.vert", program);
    fragShader = new FragShader("lighting.frag", program);

    //Link program
    glLinkProgram(program);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Create light components
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8, 1.0f};
    GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat position[] = {-1.5f, 1.0f, -4.0f, 1.0f};

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glUseProgram(program);
}

void Window::createScene() {
    figures.emplace_back(new NoelTree());
}
