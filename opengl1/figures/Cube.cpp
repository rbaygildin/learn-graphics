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

#include "Cube.h"

void Cube::draw() {
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective

    glRotatef(static_cast<GLfloat>(glfwGetTime() * 50.0f), 0, 1, 0);
    glRotatef(static_cast<GLfloat>(glfwGetTime() * 50.0f), 1, 0, 0);

    point3d a{}, b{}, c{}, d{};
    GLfloat edge = 0.25;
    point3d cen{};
    cen.x = 0;
    cen.y = 0;
    cen.z = -0.8f;

    a.x = -edge / 2 + cen.x;
    a.y = -edge / 2 + cen.y;
    a.z = -edge / 2 + cen.z;

    b.x = edge / 2 + cen.x;
    b.y = -edge / 2 + cen.y;
    b.z = -edge / 2 + cen.z;

    c.x = edge / 2 + cen.x;
    c.y = -edge / 2 + cen.y;
    c.z = edge / 2 + cen.z;

    d.x = -edge / 2 + cen.x;
    d.y = -edge / 2 + cen.y;
    d.z = edge / 2 + cen.z;

    point3d a1{}, b1{}, c1{}, d1{};
    a1.x = a.x;
    a1.y = a.y + edge;
    a1.z = a.z;

    b1.x = b.x;
    b1.y = b.y + edge;
    b1.z = b.z;

    c1.x = c.x;
    c1.y = c.y + edge;
    c1.z = c.z;

    d1.x = d.x;
    d1.y = d.y + edge;
    d1.z = d.z;

    glBegin(GL_QUADS);
    {
        //bottom
        glColor3f(RED);
        glVertex3f(VERTEX(a));
        glVertex3f(VERTEX(b));
        glVertex3f(VERTEX(c));
        glVertex3f(VERTEX(d));

        //top
        glColor3f(GREEN);
        glVertex3f(VERTEX(a1));
        glVertex3f(VERTEX(b1));
        glVertex3f(VERTEX(c1));
        glVertex3f(VERTEX(d1));

        //front
        glColor3f(BLUE);
        glVertex3f(VERTEX(a));
        glVertex3f(VERTEX(b));
        glVertex3f(VERTEX(b1));
        glVertex3f(VERTEX(a1));

        //right
        glColor3f(YELLOW);
        glVertex3f(VERTEX(b));
        glVertex3f(VERTEX(c));
        glVertex3f(VERTEX(c1));
        glColor3f(WHITE);
        glVertex3f(VERTEX(b1));

        //back
        glColor3f(WHITE);
        glVertex3f(VERTEX(c));
        glVertex3f(VERTEX(d));
        glVertex3f(VERTEX(d1));
        glVertex3f(VERTEX(c1));

        //left
        glColor3f(PINK);
        glVertex3f(VERTEX(d));
        glVertex3f(VERTEX(a));
        glVertex3f(VERTEX(a1));
        glVertex3f(VERTEX(d1));
    }
    glEnd();
}

Cube::Cube() = default;
