//
// Created by Max Heartfield on 22.11.17.
//

#include "Window.h"
#include "figures/Torus.h"
#include "figures/Sphere.h"
#include "figures/Teapot.h"
#include "figures/WireTorus.h"
#include "figures/Dodecahedron.h"

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
    if(err != GL_FALSE)
        exit(EXIT_FAILURE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    createBuffers();
    loadShaders();
    figures.emplace_back(new Cube());
    figures.emplace_back(new NoelTree());
    figures.emplace_back(new Torus(36, 36, 0.7, 0.1));
    figures.emplace_back(new Sphere(0.3f));
    figures.emplace_back(new Teapot());
    figures.emplace_back(new WireTorus(0.2, 0.09));
    figures.emplace_back(new Dodecahedron());
    initLighting();
}

Window::~Window() {
    for(auto &figure : figures)
        delete figure;
    deleteBuffers();
    deleteShaders();
    glfwDestroyWindow(wnd);
    glfwTerminate();
    BOOST_LOG_TRIVIAL(info) << "GLFW terminated. Bye!";
}

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
        for(auto &figure : figures)
            figure->draw();

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }
}

void Window::drawCube() {
}

void Window::drawTree() {

}

void Window::createBuffers() {

}

void Window::deleteBuffers() {

}

void Window::loadShaders() {
    program = glCreateProgram();
    shader = new Shader("shader.vert", "shader.frag", program);
    lightShader = new Shader("lighting.vert", "lighting.frag", program);
    glLinkProgram(program);
    glUseProgram(program);
}

void Window::deleteShaders() {
    if(!shader)
        delete shader;
    if(!lightShader)
        delete lightShader;
}

void Window::initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat diffuseLight[] = {0.4, 0.7, 0.2, 1.0f};
    GLfloat specularLight[] = { 0.5f, 0.2f, 0.5f, 1.0f };
    GLfloat position[] = { 0.0f, 1.0f, -10.0f, 0.0f };

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
