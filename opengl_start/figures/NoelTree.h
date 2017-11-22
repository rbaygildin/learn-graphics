//
// Created by Max Heartfield on 22.11.17.
//

#ifndef OPENGL_START_NOELTREE_H
#define OPENGL_START_NOELTREE_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Figure.h"

class NoelTree : public Figure{
public:
    NoelTree();
    ~NoelTree();

    void draw() override;

private:
    const static int N = 3;
    const static int V = 3;
    const static int SV = 200;
    GLuint vertexVao;
    GLuint colorVao;
    GLuint starVertexVao;
    GLuint starColorVao;
};


#endif //OPENGL_START_NOELTREE_H
