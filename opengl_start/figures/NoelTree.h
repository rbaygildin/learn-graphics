//
// Created by Max Heartfield on 22.11.17.
//

#ifndef OPENGL_START_NOELTREE_H
#define OPENGL_START_NOELTREE_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Figure.h"

class NoelTree : public Figure{
public:
    NoelTree();
    ~NoelTree();

    void draw() override;

private:
    const static int FACES_COUNT = 4;
    const static int FACE_VERTEX_COUNT = 3;
    GLuint vertexVao;
    GLuint colorVao;

};


#endif //OPENGL_START_NOELTREE_H
