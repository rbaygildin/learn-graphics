//
// Created by Max Heartfield on 22.11.17.
//

#include "Cube.h"

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vertex;

void Cube::draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(static_cast<GLfloat>(glfwGetTime() * 10.0f), 0, 1, 1);
    glTranslatef(-0.5f, -0.5f, 0);
    //bottom
    vertex A;
    A.x = -0.25f;
    A.y = -0.325f;
    A.z = 0.25f;
    vertex B;
    B.x = 0.25f;
    B.y = -0.325f;
    B.z = 0.25f;
    vertex C;
    C.x = 0.25f;
    C.y = -0.325f;
    C.z = -0.25f;
    vertex D;
    D.x = -0.250f;
    D.y = -0.325f;
    D.z = -0.25f;

    glBegin(GL_QUADS);
    {
        //front
        glColor3f(1, 0, 0);
        glVertex3f(A.x, A.y + 0.5f, A.z);
        glColor3f(0, 1, 0);
        glVertex3f(B.x, B.y + 0.5f, B.z);
        glColor3f(0, 0, 1);
        glVertex3f(B.x, B.y, B.z);
        glColor3f(0, 1, 1);
        glVertex3f(A.x, A.y, A.z);
        //right
        glColor3f(1, 0, 0);
        glVertex3f(B.x, B.y + 0.5f, B.z);
        glColor3f(0, 1, 0);
        glVertex3f(C.x, C.y + 0.5f, C.z);
        glColor3f(0, 0, 1);
        glVertex3f(C.x, C.y, C.z);
        glColor3f(0, 1, 1);
        glVertex3f(B.x, B.y, B.z);
        //back
        glColor3f(1, 0, 0);
        glVertex3f(C.x, C.y, C.z);
        glColor3f(0, 1, 0);
        glVertex3f(D.x, D.y, D.z);
        glColor3f(0, 0, 1);
        glVertex3f(D.x, D.y + 0.5f, D.z);
        glColor3f(0, 1, 1);
        glVertex3f(C.x, C.y + 0.5f, C.z);
        //left
        glColor3f(1, 0, 0);
        glVertex3f(D.x, D.y + 0.5f, D.z);
        glColor3f(0, 1, 0);
        glVertex3f(A.x, A.y + 0.5f, A.z);
        glColor3f(0, 0, 1);
        glVertex3f(A.x, A.y, A.z);
        glColor3f(0, 1, 1);
        glVertex3f(D.x, D.y, D.z);
        //bottom
        glColor3f(1, 0, 0);
        glVertex3f(B.x, B.y, B.z);
        glColor3f(0, 1, 0);
        glVertex3f(C.x, C.y, C.z);
        glColor3f(0, 0, 1);
        glVertex3f(D.x, D.y, D.z);
        glColor3f(0, 1, 1);
        glVertex3f(A.x, A.y, A.z);
        //top
        glColor3f(1, 0, 0);
        glVertex3f(B.x, B.y + 0.5f, B.z);
        glColor3f(0, 1, 0);
        glVertex3f(C.x, C.y + 0.5f, C.z);
        glColor3f(0, 0, 1);
        glVertex3f(D.x, D.y + 0.5f, D.z);
        glColor3f(0, 1, 1);
        glVertex3f(A.x, A.y + 0.5f, A.z);
    }
    glEnd();
}

Cube::Cube() {

}
