//
// Created by Max Heartfield on 23.11.17.
//

#include "Dodecahedron.h"
#include "../common.h"

void Dodecahedron::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glScalef(scaleCoeff, scaleCoeff, scaleCoeff);
    glTranslatef(-0.8f, -0.8f, -0.9f);
    glColor3f(GREEN);
    glutWireDodecahedron();
    glPopMatrix();
}
