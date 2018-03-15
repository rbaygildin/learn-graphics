//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_GREENFILTER_H
#define OPENGL_GREENFILTER_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class GreenFilter : public QOpenGLShaderProgram {
public:
    GreenFilter();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/greenFilter.frag";
};


#endif //OPENGL_GREENFILTER_H
