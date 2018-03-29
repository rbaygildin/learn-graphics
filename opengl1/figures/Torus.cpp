// Copyright 2016 - Roman Yarnykh. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Torus.h"

void Torus::draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(static_cast<GLfloat>(glfwGetTime() * 20.0f), 0, 1, 0);
    glRotatef(static_cast<GLfloat>(glfwGetTime() * 50.0f), 1, 0, 0);
    Matrix vs(static_cast<unsigned long>(vCount * hCount), 3);
    for (ULONG column = 0; column < hCount; column++) {
        for (ULONG row = 0; row < vCount; row++) {
            std::vector<GLfloat> coords = getCoords(row, column);
            vs(row * hCount + column, 0) = coords[0];
            vs(row * hCount + column, 1) = coords[1];
            vs(row * hCount + column, 2) = coords[2];
        }
    }
    vector<vector<GLfloat>> vboVector;
    for (ULONG col = 1; col < hCount; col++) {
        for (ULONG row = 1; row < vCount; row++) {
            vector<GLfloat> v1, v2, v3, v4;
            for (ULONG coord = 0; coord < 3; coord++) {
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
        for (ULONG coord = 0; coord < 3; coord++) {
            v1.emplace_back(vs(static_cast<unsigned long>(row * vCount), coord));
            v2.emplace_back(vs(static_cast<unsigned long>((row - 1) * hCount), coord));
            v3.emplace_back(vs(static_cast<unsigned long>((row - 1) * hCount + hCount - 1), coord));
            v4.emplace_back(vs(static_cast<unsigned long>(row * hCount + hCount - 1), coord));
        }
        vboVector.emplace_back(v1);
        vboVector.emplace_back(v2);
        vboVector.emplace_back(v3);
        vboVector.emplace_back(v4);
    }

    glColor3f(GREEN);
    glBegin(GL_QUADS);
    for (auto &i : vboVector)
        glVertex3f(i[0], i[1], i[2]);
    glEnd();
}

Torus::Torus(int vCount, int hCount, GLfloat R, GLfloat r) {
    this->vCount = vCount;
    this->hCount = hCount;
    this->R = R;
    this->r = r;
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
    for (int i = 0; i < vCount * hCount; i++)
        glDeleteBuffers(1, &facesVao[i]);
    delete[] facesVao;
}
