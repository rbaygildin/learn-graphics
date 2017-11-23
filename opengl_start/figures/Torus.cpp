//
// Created by Max Heartfield on 23.11.17.
//

#include "Torus.h"

void Torus::draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(static_cast<GLfloat>(glfwGetTime() * 20.0f), 0, 1, 0);
    glRotatef(static_cast<GLfloat>(glfwGetTime() * 50.0f), 1, 0, 0);

//    glBindBuffer(GL_ARRAY_BUFFER, vao);
//    glVertexPointer(4, GL_FLOAT, 0, nullptr);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_COLOR);
//    glColor3f(BLUE);
//    glDrawArrays(GL_QUADS, 0, vCount * hCount * 4);
    glColor3f(BLUE);
//    glutSolidTorus(r, R, vCount, hCount);

    Matrix vs(vCount * hCount, 3);
    for (ULONG column = 0; column < hCount; column++) {
        for (ULONG row = 0; row < vCount; row++) {
            std::vector<GLfloat> coords = getCoords(row, column);
            vs(row * hCount + column, 0) = coords[0];
            vs(row * hCount + column, 1) = coords[1];
            vs(row * hCount + column, 2) = coords[2];
        }
    }
    vector<vector<GLfloat>> vboVector;
//    auto **vbo = new GLfloat*[vCount * hCount * 4];
//    for(ULONG col = 1; col < hCount; col++){
//        for(ULONG row = 1; row < vCount; row++){
//            ULONG index = (col * vCount + row) * 4;
//            vbo[index] = new GLfloat[3];
//            vbo[index + 1] = new GLfloat[3];
//            vbo[index + 2] = new GLfloat[3];
//            vbo[index + 3] = new GLfloat[3];
//            for(ULONG coord = 0; coord < 3; coord++){
//                vbo[index + 0][coord] = vs(row * hCount + col, coord);
//                vbo[index + 1][coord] = vs((row - 1) * hCount + col, coord);
//                vbo[index + 2][coord] = vs((row - 1) * hCount + col - 1, coord);
//                vbo[index + 3][coord] = vs(row * hCount + col - 1, coord);
//            }
//        }
//    }
    for(ULONG col = 1; col < hCount; col++){
        for(ULONG row = 1; row < vCount; row++){
            vector<GLfloat> v1, v2, v3, v4;
            for(ULONG coord = 0; coord < 3; coord++){
                v1.emplace_back(vs(row * hCount + col, coord));
                v2.emplace_back(vs((row - 1) * hCount + col, coord));
                v3.emplace_back(vs((row - 1) * hCount + col - 1, coord));
                v4.emplace_back(vs(row * hCount + col - 1, coord));
            }
            vboVector.emplace_back(v1);
            vboVector.emplace_back(v2);
            vboVector.emplace_back(v3);
            vboVector.emplace_back(v4);
        }
    }
    for (int row = 1; row < vCount; row++) {
        vector<GLfloat> v1, v2, v3, v4;
        for(ULONG coord = 0; coord < 3; coord++){
            v1.emplace_back(vs(row * vCount, coord));
            v2.emplace_back(vs((row - 1) * hCount, coord));
            v3.emplace_back(vs((row - 1) * hCount + hCount - 1, coord));
            v4.emplace_back(vs(row * hCount + hCount - 1, coord));
        }
        vboVector.emplace_back(v1);
        vboVector.emplace_back(v2);
        vboVector.emplace_back(v3);
        vboVector.emplace_back(v4);
    }
    glBegin(GL_QUADS);
    for(int i = 0; i < vboVector.size(); i++)
        glVertex3f(vboVector[i][0], vboVector[i][1], vboVector[i][2]);
    glEnd();

    glutWireTetrahedron();
}

Torus::Torus(int vCount, int hCount, GLfloat R, GLfloat r) {
    this->vCount = vCount;
    this->hCount = hCount;
    this->R = R;
    this->r = r;
    Matrix vs(vCount * hCount, 3);
    for (ULONG column = 0; column < hCount; column++) {
        for (ULONG row = 0; row < vCount; row++) {
            std::vector<GLfloat> coords = getCoords(row, column);
            vs(row * hCount + column, 0) = coords[0];
            vs(row * hCount + column, 1) = coords[1];
            vs(row * hCount + column, 2) = coords[2];
        }
    }
    vector<vector<GLfloat>> vboVector;
//    auto **vbo = new GLfloat*[vCount * hCount * 4];
//    for(ULONG col = 1; col < hCount; col++){
//        for(ULONG row = 1; row < vCount; row++){
//            ULONG index = (col * vCount + row) * 4;
//            vbo[index] = new GLfloat[3];
//            vbo[index + 1] = new GLfloat[3];
//            vbo[index + 2] = new GLfloat[3];
//            vbo[index + 3] = new GLfloat[3];
//            for(ULONG coord = 0; coord < 3; coord++){
//                vbo[index + 0][coord] = vs(row * hCount + col, coord);
//                vbo[index + 1][coord] = vs((row - 1) * hCount + col, coord);
//                vbo[index + 2][coord] = vs((row - 1) * hCount + col - 1, coord);
//                vbo[index + 3][coord] = vs(row * hCount + col - 1, coord);
//            }
//        }
//    }
    for(ULONG col = 1; col < hCount; col++){
        for(ULONG row = 1; row < vCount; row++){
            vector<GLfloat> v1, v2, v3, v4;
            for(ULONG coord = 0; coord < 3; coord++){
                v1.emplace_back(vs(row * hCount + col, coord));
                v2.emplace_back(vs((row - 1) * hCount + col, coord));
                v3.emplace_back(vs((row - 1) * hCount + col - 1, coord));
                v4.emplace_back(vs(row * hCount + col - 1, coord));
            }
            vboVector.emplace_back(v1);
            vboVector.emplace_back(v2);
            vboVector.emplace_back(v3);
            vboVector.emplace_back(v4);
        }
    }
    for (int row = 1; row < vCount; row++) {
        vector<GLfloat> v1, v2, v3, v4;
        for(ULONG coord = 0; coord < 3; coord++){
            v1.emplace_back(vs(row * vCount, coord));
            v2.emplace_back(vs((row - 1) * hCount, coord));
            v3.emplace_back(vs((row - 1) * hCount + hCount - 1, coord));
            v4.emplace_back(vs(row * hCount + hCount - 1, coord));
        }
        vboVector.emplace_back(v1);
        vboVector.emplace_back(v2);
        vboVector.emplace_back(v3);
        vboVector.emplace_back(v4);
    }
    auto vbo = new GLfloat*[vboVector.size()];
    for(size_t i = 0; i < vboVector.size(); i++) {
        vbo[i] = new GLfloat[3];
        for (size_t j = 0; j < 3; j++)
            vbo[i][j] = vboVector[i][j];
    }

    glGenBuffers(1, &vao);
    glBindBuffer(GL_ARRAY_BUFFER, vao);
    glBufferData(GL_ARRAY_BUFFER, vboVector.size() * 3 * sizeof(GLfloat), vbo, GL_STATIC_DRAW);
}

vector<GLfloat> Torus::getCoords(ULONG row, ULONG column) {
    GLfloat phi = 2 * 3.1459f / hCount * row - 3.1459f;
    GLfloat xi = 2 * 3.1459f / vCount * column;
    std::vector<GLfloat> res(3);
    res[0] = (R + r * cos(phi)) * cos(xi);
    res[1] = (R + r * cos(phi)) * sin(xi);
    res[2] = r * sin(phi);
    return res;
}

Torus::~Torus() {
    glDeleteBuffers(1, &vao);
}
