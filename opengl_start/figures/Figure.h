//
// Created by Max Heartfield on 22.11.17.
//

#ifndef OPENGL_START_FIGURE_H
#define OPENGL_START_FIGURE_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Figure {
public:
    virtual void draw() = 0;
};


#endif //OPENGL_START_FIGURE_H
