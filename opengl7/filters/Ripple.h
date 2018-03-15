//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_RIPPLE_H
#define OPENGL_RIPPLE_H


#include <QOpenGLShaderProgram>
#include "../utils.h"

class Ripple : public QOpenGLShaderProgram {
public:
    Ripple();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/ripple.frag";
};


#endif //OPENGL_RIPPLE_H
