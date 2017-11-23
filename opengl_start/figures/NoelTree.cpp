//
// Created by Max Heartfield on 22.11.17.
//

#include "NoelTree.h"

NoelTree::NoelTree() {
    static GLfloat vertexVbo[N * V][3] = {
            //Tree
            {0.5f, 0, 0.001f},
            {0, 0.5f, 0.001f},
            {-0.5f, 0, 0.001f},

            {0, 0.25, 0.0001f},
            {0.5f, -0.25f, 0.0001f},
            {-0.5f, -0.25f, 0.0001f},

            {0, 0.f, 0},
            {0.5f, -0.5f, 0},
            {-0.5f, -0.5f, 0},
    };
    static GLfloat colorVbo[N * V][3] = {
            {0, 1, 0.2},
            {0, 1, 0.5},
            {0, 1, 0.4},

            {0, 1, 0.2},
            {0, 0.8, 0.5},
            {0, 0.8, 0.4},

            {0, 1, 0.2},
            {0, 0.7, 0.5},
            {0, 0.7, 0.4},
    };

    GLfloat starVertexVbo[SV][V];
    GLfloat ang = 2 * 3.1459f / SV;
    for(int i = 0; i < SV - 1; i++){
        starVertexVbo[i][0] = 0.f + cos(ang * i) * 0.1f;
        starVertexVbo[i][1] = 0.5f + sin(ang * i) * 0.1f;
        starVertexVbo[i][2] = 0.01f;
    }
    starVertexVbo[SV - 1][0] = 0.f + cos(0.f) * 0.1f;
    starVertexVbo[SV - 1][1] = 0.5f + sin(0.f) * 0.1f;
    starVertexVbo[SV - 1][2] = 0.01f;

    glGenBuffers(1, &vertexVao);
    glGenBuffers(1, &colorVao);
    glGenBuffers(1, &starVertexVao);

    /* Vertex data */
    glBindBuffer(GL_ARRAY_BUFFER, vertexVao);
    glBufferData(GL_ARRAY_BUFFER, N * V * 3 * sizeof(GLfloat), vertexVbo, GL_STATIC_DRAW);

    /* Color data */
    glBindBuffer(GL_ARRAY_BUFFER, colorVao);
    glBufferData(GL_ARRAY_BUFFER, N * V * 3 * sizeof(GLfloat), colorVbo, GL_STATIC_DRAW);

    /* Vertex data */
    glBindBuffer(GL_ARRAY_BUFFER, starVertexVao);
    glBufferData(GL_ARRAY_BUFFER, SV * V * sizeof(GLfloat), starVertexVbo, GL_STATIC_DRAW);
}


void NoelTree::draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Vertex data */
    glBindBuffer(GL_ARRAY_BUFFER, vertexVao);
    glVertexPointer(V, GL_FLOAT, 0, nullptr);
    glEnableClientState(GL_VERTEX_ARRAY);

    /* Color data */
    glBindBuffer(GL_ARRAY_BUFFER, colorVao);
    glColorPointer(V, GL_FLOAT, 0, nullptr);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays(GL_TRIANGLES, 0, N * V);

    glDisableClientState(GL_COLOR_ARRAY);

    glColor3f(0.8, 0.0, 0.0);
    /* Vertex data */
    glBindBuffer(GL_ARRAY_BUFFER, starVertexVao);
    glVertexPointer(V, GL_FLOAT, 0, nullptr);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POLYGON, 0, SV * V);
}

NoelTree::~NoelTree() {
    glDeleteBuffers(1, &vertexVao);
    glDeleteBuffers(1, &colorVao);
}