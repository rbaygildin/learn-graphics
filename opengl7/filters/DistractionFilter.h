//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_DISTRACTIONFILTER_H
#define OPENGL_DISTRACTIONFILTER_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class DistractionFilter : public QOpenGLShaderProgram{
public:
    DistractionFilter();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/distraction.frag";
};


#endif //OPENGL_DISTRACTIONFILTER_H
