//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_SHARPENFILTER_H
#define OPENGL_SHARPENFILTER_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class SharpenFilter : public QOpenGLShaderProgram{
public:
    SharpenFilter();

private:
    static constexpr auto VERT_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/sharpen.frag";
};


#endif //OPENGL_SHARPENFILTER_H
