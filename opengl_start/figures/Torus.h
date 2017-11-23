//
// Created by Max Heartfield on 23.11.17.
//

#ifndef OPENGL_START_TORUS_H
#define OPENGL_START_TORUS_H


#include "Figure.h"
#include <vector>
#include "../common.h"
#include <GLUT/glut.h>

using namespace std;

class Torus : public Figure {
public:
    Torus(int vCount, int hCount, GLfloat R, GLfloat r);
    ~Torus();
    void draw() override;

private:
    vector<GLfloat> getCoords(ULONG row, ULONG column);

    int hCount, vCount;
    GLfloat R, r;
    GLuint vao;
};


#endif //OPENGL_START_TORUS_H
