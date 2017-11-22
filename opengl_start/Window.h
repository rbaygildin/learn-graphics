//
// Created by Max Heartfield on 22.11.17.
//

#ifndef OPENGL_START_WINDOW_H
#define OPENGL_START_WINDOW_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "shaders/Shader.h"
#include "figures/Figure.h"

using namespace std;

class Window {
public:
    Window();

    ~Window();

    void run();

private:
    static void errorCallback(int error, const char *description);

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void mouseCallback(GLFWwindow *window, double xPos, double yPos);

    void loadContext();

private:
    GLuint vertexes;
    GLuint colors;
    GLuint program;
    GLFWwindow *wnd;
    Shader* vertexShader;
    Shader *fragShader;
    vector<Figure*> figures;
    static float alpha;

    void createScene();
};


#endif //OPENGL_START_WINDOW_H
