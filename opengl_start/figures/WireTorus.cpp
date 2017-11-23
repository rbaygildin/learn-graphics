//
// Created by Max Heartfield on 23.11.17.
//

#include "WireTorus.h"

void WireTorus::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.5, 0, 0.5);
    glutWireTorus(r, R, 36, 36);
    glPopMatrix();
}

WireTorus::WireTorus(GLfloat R, GLfloat r) {
    this->R = R;
    this->r = r;
}
