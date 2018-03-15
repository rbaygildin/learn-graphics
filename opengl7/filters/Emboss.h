//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_EMBOSS_H
#define OPENGL_EMBOSS_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class Emboss : public QOpenGLShaderProgram {
public:
    Emboss();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/emboss.frag";
};


#endif //OPENGL_EMBOSS_H
