//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_REDFILTER_H
#define OPENGL_REDFILTER_H


#include <QOpenGLShaderProgram>
#include "../utils.h"

class RedFilter : public QOpenGLShaderProgram {

public:
    RedFilter();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/redFilter.frag";
};


#endif //OPENGL_REDFILTER_H
