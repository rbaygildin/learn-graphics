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

#ifndef OPENGL_START_NOELTREE_H
#define OPENGL_START_NOELTREE_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Figure.h"

class NoelTree : public Figure{
public:
    NoelTree();
    ~NoelTree();

    void draw() override;

private:
    const static int N = 3;
    const static int V = 3;
    const static int SV = 200;
    GLuint vertexVao;
    GLuint colorVao;
    GLuint starVertexVao;
    GLuint starColorVao;
};


#endif //OPENGL_START_NOELTREE_H
