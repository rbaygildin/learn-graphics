//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_ABERRATIONFILTER_H
#define OPENGL_ABERRATIONFILTER_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class AberrationFilter : public QOpenGLShaderProgram {
public:
    AberrationFilter();

private:
    static constexpr auto VERT_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/aberration.frag";
};


#endif //OPENGL_ABERRATIONFILTER_H
