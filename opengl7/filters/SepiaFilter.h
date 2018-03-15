//
// Created by Max Heartfield on 13.03.18.
//

#ifndef OPENGL_SEPIAFILTER_H
#define OPENGL_SEPIAFILTER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include "../utils.h"

class SepiaFilter : public QOpenGLShaderProgram {
public:
    SepiaFilter();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/sepia.frag";
};


#endif //OPENGL_SEPIAFILTER_H
