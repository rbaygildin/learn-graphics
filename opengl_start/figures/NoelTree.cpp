//
// Created by Max Heartfield on 22.11.17.
//

#include "NoelTree.h"

NoelTree::NoelTree() {
    static GLfloat vertexVbo[FACES_COUNT][FACE_VERTEX_COUNT] = {
            {0.5f,  0.5f,  0.0f},
            {-0.5f, 0.5f,  0.0f},
            {-0.5f, -0.5f, 0.0f},
            {0.5f,  -0.5f, 0.0f}
    };
    static GLfloat colorVbo[FACES_COUNT][FACE_VERTEX_COUNT] = {
            {1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {0.0, 0.0, 1.0},
            {1.0, 1.0, 1.0}
    };
    glGenBuffers(1, &vertexVao);
    glGenBuffers(1, &colorVao);

    /* Vertex data */
    glBindBuffer(GL_ARRAY_BUFFER, vertexVao);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), vertexVbo, GL_STATIC_DRAW);

    /* Color data */
    glBindBuffer(GL_ARRAY_BUFFER, colorVao);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), colorVbo, GL_STATIC_DRAW);
}


void NoelTree::draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef((float) glfwGetTime() * 50.f, 1.0, 1.0f, 0.0f);

    /* Vertex data */
    glBindBuffer(GL_ARRAY_BUFFER, vertexVao);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glEnableClientState(GL_VERTEX_ARRAY);

    /* Color data */
    glBindBuffer(GL_ARRAY_BUFFER, colorVao);
    glColorPointer(3, GL_FLOAT, 0, nullptr);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays(GL_POLYGON, 0, 4);
}

NoelTree::~NoelTree() {
    glDeleteBuffers(1, &vertexVao);
    glDeleteBuffers(1, &colorVao);
}