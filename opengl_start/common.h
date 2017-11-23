//
// Created by Max Heartfield on 23.11.17.
//

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
#define LIGHT_GRAY 0.4f, 0.4f, 0.4f
#define PINK 1.0f, 0.25f, 0.56f

#define D2R(DEGREE) (DEGREE * M_PI / 180)

typedef boost::numeric::ublas::matrix<GLfloat> Matrix;
typedef unsigned long ULONG;

struct point3d {
    GLfloat x, y, z;
};


#endif //OPENGL_START_COMMON_H
