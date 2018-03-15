//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_REFLECTIONFILTER_H
#define OPENGL_REFLECTIONFILTER_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class ReflectionFilter : public QOpenGLShaderProgram {
public:
    ReflectionFilter();

private:
    static constexpr auto VERT_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/reflection.frag";
};


#endif //OPENGL_REFLECTIONFILTER_H
