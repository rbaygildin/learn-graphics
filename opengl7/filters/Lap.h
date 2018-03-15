//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_LAP_H
#define OPENGL_LAP_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class Lap : public QOpenGLShaderProgram {
public:
    Lap();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/lap.frag";
};

#endif //OPENGL_LAP_H
