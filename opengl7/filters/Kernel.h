//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_KERNEL_H
#define OPENGL_KERNEL_H


#include <QOpenGLShaderProgram>
#include "../utils.h"

class Kernel : public QOpenGLShaderProgram {
public:
    Kernel();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/kernel.frag";
};


#endif //OPENGL_KERNEL_H
