//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_GRAYSCALEFILTER_H
#define OPENGL_GRAYSCALEFILTER_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class GrayscaleFilter : public QOpenGLShaderProgram {
public:
    GrayscaleFilter();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/grayscale.frag";
};


#endif //OPENGL_GRAYSCALEFILTER_H
