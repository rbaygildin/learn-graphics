//
// Created by Max Heartfield on 23.11.17.
//

#include "Sphere.h"

void Sphere::draw() {
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(glfwGetTime() * 20.0f, 0, 1, 0);
    glutWireSphere(r, 36, 36);
    glPopMatrix();
}

Sphere::Sphere(GLfloat r) {
    this->r = r;
}
