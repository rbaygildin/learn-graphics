////
////  main.cpp
////  opengl_start
////
////  Created by Roman Yarnykh on 12.11.17.
////  Copyright © 2017 Roman Yarnykh. All rights reserved.
////


#define GL_GLEXT_PROTOTYPES

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

GLuint vertexes;
GLuint colors;

GLuint program;
GLuint vertexShader;
GLuint fragShader;

void loadShaders(const string &, const string &);

void createBuffers();

void display(GLFWwindow *wnd);

void deleteBuffers();

string readFile(const string &);

static void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char **argv) {
    GLFWwindow *window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

//    glfwWindowHint(GLFW_SAMPLES, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Simple example", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetKeyCallback(window, key_callback);
    createBuffers();
    loadShaders("shader.vert", "shader.frag");
    display(window);
    deleteBuffers();
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

string readFile(const string &path) {
    ifstream f(path);
    stringstream s;
    s << f.rdbuf();
    f.close();
    return s.str();
}

void createBuffers() {
    static const GLfloat planeVertexes[4][3] = {
            {0.5f,  0.5f,  0.0f},
            {-0.5f, 0.5f,  0.0f},
            {-0.5f, -0.5f, 0.0f},
            {0.5f,  -0.5f, 0.0f}
    };

    static const GLfloat planeColors[4][3] = {
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0},
            {1.0, 1.0, 1.0}
    };

    glGenBuffers(1, &vertexes);
    glGenBuffers(1, &colors);

    /* Vertex data */
    glBindBuffer(GL_ARRAY_BUFFER, vertexes);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), planeVertexes, GL_STATIC_DRAW);

    /* Color data */
    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), planeColors, GL_STATIC_DRAW);
}

void loadShaders(const string &vertexShaderPath, const string &fragShaderPath) {
    program = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    string vs = readFile(vertexShaderPath);
    string fs = readFile(fragShaderPath);
    const char *vsSource = vs.c_str();
    const char *fsSource = fs.c_str();
    auto vsLen = static_cast<GLint>(vs.length());
    auto fsLen = static_cast<GLint>(fs.length());
    glShaderSource(vertexShader, 1, &vsSource, &vsLen);
    glShaderSource(fragShader, 1, &fsSource, &fsLen);
    GLint success = 0;
    cout << "Compiling vertex shader" << endl;
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        cout << "Compilation vertex shader failed!";
    }
    cout << "Compiling fragment shader" << endl;
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        cout << "Compilation frag shader failed!";
    }
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
}

void display(GLFWwindow *wnd) {
    while (!glfwWindowShouldClose(wnd)) {
//        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glMatrixMode(GL_MODELVIEW);
//        glUseProgram(program);
//
//        /* Vertex data */
//        glBindBuffer(GL_ARRAY_BUFFER, vertexes);
//        glVertexPointer(3, GL_FLOAT, 0, nullptr);
//        glEnableClientState(GL_VERTEX_ARRAY);
//
//        /* Color data */
//        glBindBuffer(GL_ARRAY_BUFFER, colors);
//        glColorPointer(3, GL_FLOAT, 0, nullptr);
//        glEnableClientState(GL_COLOR_ARRAY);
//
//        glDrawArrays(GL_POLYGON, 0, 4);
//        glfwSwapBuffers(wnd);
//        glfwPollEvents();
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
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

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

void deleteBuffers() {
    glDeleteBuffers(1, &vertexes);
    glDeleteBuffers(1, &colors);
}
