//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_GAMMAFILTER_H
#define OPENGL_GAMMAFILTER_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class GammaFilter : public QOpenGLShaderProgram {
public:
    GammaFilter();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/gamma.frag";
};


#endif //OPENGL_GAMMAFILTER_H
