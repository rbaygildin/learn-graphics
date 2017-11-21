//
// Created by Max Heartfield on 22.11.17.
//

#include "Window.h"
#include "shaders/VertexShader.h"
#include "shaders/FragShader.h"

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
    loadContext();
}

Window::~Window() {
    delete vertexShader;
    delete fragShader;
    glDeleteBuffers(1, &vertexes);
    glDeleteBuffers(1, &colors);
    glfwDestroyWindow(wnd);
    glfwTerminate();
}

void Window::run() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Create light components
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_COLOR_MATERIAL);

    while (!glfwWindowShouldClose(wnd)) {
        glUseProgram(program);
        float ratio;
        int width, height;
        glfwGetFramebufferSize(wnd, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, (float) glfwGetTime() * 10.f, 0.f, 1.f);

        /* Vertex data */
        glBindBuffer(GL_ARRAY_BUFFER, vertexes);
        glVertexPointer(3, GL_FLOAT, 0, nullptr);
        glEnableClientState(GL_VERTEX_ARRAY);

        /* Color data */
        glBindBuffer(GL_ARRAY_BUFFER, colors);
        glColorPointer(3, GL_FLOAT, 0, nullptr);
        glEnableClientState(GL_COLOR_ARRAY);

        glDrawArrays(GL_POLYGON, 0, 4);

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
    //Create buffers
    static const GLfloat vertexVao[4][3] = {
            {0.5f,  0.5f,  0.0f},
            {-0.5f, 0.5f,  0.0f},
            {-0.5f, -0.5f, 0.0f},
            {0.5f,  -0.5f, 0.0f}
    };

    static const GLfloat colorsVao[4][3] = {
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0},
            {1.0, 1.0, 1.0}
    };

    glGenBuffers(1, &vertexes);
    glGenBuffers(1, &colors);

    /* Vertex data */
    glBindBuffer(GL_ARRAY_BUFFER, vertexes);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), vertexVao, GL_STATIC_DRAW);

    /* Color data */
    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), colorsVao, GL_STATIC_DRAW);

    //Create program
    program = glCreateProgram();

    //Load shaders
    vertexShader = new VertexShader("lighting.vert", program);
    fragShader = new FragShader("lighting.frag", program);

    //Link program
    glLinkProgram(program);
}
