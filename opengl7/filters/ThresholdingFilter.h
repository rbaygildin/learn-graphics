//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_THRESHOLDINGFILTER_H
#define OPENGL_THRESHOLDINGFILTER_H

#include <QOpenGLShaderProgram>
#include "../utils.h"

class ThresholdingFilter : public QOpenGLShaderProgram {
public:
    ThresholdingFilter();

private:
    static constexpr auto VERT_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/thresholding.frag";
};


#endif //OPENGL_THRESHOLDINGFILTER_H
