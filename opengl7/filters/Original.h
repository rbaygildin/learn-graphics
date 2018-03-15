//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_ORIGINAL_H
#define OPENGL_ORIGINAL_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class Original : public QOpenGLShaderProgram {
public:
    Original();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/original.frag";
};


#endif //OPENGL_ORIGINAL_H
