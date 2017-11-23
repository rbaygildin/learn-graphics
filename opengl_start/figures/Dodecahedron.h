//
// Created by Max Heartfield on 23.11.17.
//

#ifndef OPENGL_START_DODECAHEDRON_H
#define OPENGL_START_DODECAHEDRON_H


#include "Figure.h"

class Dodecahedron : public Figure{
public:
    void draw() override;

private:
    GLfloat scaleCoeff = 0.1;
};


#endif //OPENGL_START_DODECAHEDRON_H
