//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_BLUEFILTER_H
#define OPENGL_BLUEFILTER_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class BlueFilter : public QOpenGLShaderProgram {

public:
    BlueFilter();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/blueFilter.frag";
};


#endif //OPENGL_BLUEFILTER_H
