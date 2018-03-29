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

#ifndef OPENGL_START_COMMON_H
#define OPENGL_START_COMMON_H

#include <GL/glew.h>
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>

#define COMMA ,
#define VERTEX(POINT) POINT.x COMMA POINT.y COMMA POINT.z

#define RED 1.0f, 0.0f, 0.0f
#define GREEN 0.0F, 1.0f, 0.0f
#define BLUE 0.0f, 0.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f
#define YELLOW 0.0f, 1.0f, 1.0f
#define DARK_GRAY 0.2f, 0.2f, 0.2f
#define PINK 1.0f, 0.25f, 0.56f

typedef boost::numeric::ublas::matrix<GLfloat> Matrix;
typedef unsigned long ULONG;

struct point3d {
    GLfloat x, y, z;
};


#endif //OPENGL_START_COMMON_H
