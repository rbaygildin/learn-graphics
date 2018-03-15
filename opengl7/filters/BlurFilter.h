//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_BLURFILTER_H
#define OPENGL_BLURFILTER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include "../utils.h"

class BlurFilter : public QOpenGLShaderProgram {
public:
    BlurFilter();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/blur.frag";
};


#endif //OPENGL_BLURFILTER_H
