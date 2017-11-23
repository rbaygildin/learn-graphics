//
// Created by Max Heartfield on 23.11.17.
//

#include "Teapot.h"
#include "../common.h"

void Teapot::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(RED);
    glRotatef(static_cast<GLfloat>(glfwGetTime() * 10.0f), 1, 0, 0);
    glRotatef(static_cast<GLfloat>(glfwGetTime() * 10.0f), 0, 1, 1);
    glTranslatef(0, 0, -0.8f);
    glutSolidTeapot(0.2);
    glPopMatrix();
}
