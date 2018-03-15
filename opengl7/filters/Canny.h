//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_CANNY_H
#define OPENGL_CANNY_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class Canny : public QOpenGLShaderProgram {
public:
    Canny();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/canny.frag";
};


#endif //OPENGL_CANNY_H
