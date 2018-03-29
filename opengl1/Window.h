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

#ifndef OPENGL_START_WINDOW_H
#define OPENGL_START_WINDOW_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <boost/log/trivial.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "shaders/Shader.h"
#include "figures/Figure.h"
#include "figures/Cube.h"
#include "figures/NoelTree.h"

using namespace std;

enum Mode {
    X, Y
};

class Window {
public:
    Window();

    ~Window();

    void run();

private:
    void initLighting();

    void loadShaders();

    void deleteShaders();

    void createBuffers();

    void deleteBuffers();

private:
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    GLFWwindow *wnd;
    Shader *shader;
    Shader *lightShader;
    GLuint program;
    vector<Figure *> figures;
};


#endif //OPENGL_START_WINDOW_H
