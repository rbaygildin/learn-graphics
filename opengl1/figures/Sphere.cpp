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

#include "Sphere.h"

void Sphere::draw() {
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(static_cast<GLfloat>(glfwGetTime() * 20.0f), 0, 1, 0);
    glutWireSphere(r, 36, 36);
    glPopMatrix();
}

Sphere::Sphere(GLfloat r) {
    this->r = r;
}
