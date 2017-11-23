//
// Created by Max Heartfield on 23.11.17.
//

#ifndef OPENGL_START_WIRETORUS_H
#define OPENGL_START_WIRETORUS_H


#include "Figure.h"

class WireTorus : public Figure {
public:
    WireTorus(GLfloat R, GLfloat r);

    void draw() override;

private:
    GLfloat R;
    GLfloat r;
};


#endif //OPENGL_START_WIRETORUS_H
