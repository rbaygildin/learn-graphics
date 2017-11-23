//
// Created by Max Heartfield on 23.11.17.
//

#ifndef OPENGL_START_SPHERE_H
#define OPENGL_START_SPHERE_H


#include "Figure.h"
#include <GLUT/glut.h>

class Sphere : public Figure {
public:
    explicit Sphere(GLfloat r);

    void draw() override;

private:
    GLfloat r;

};


#endif //OPENGL_START_SPHERE_H
