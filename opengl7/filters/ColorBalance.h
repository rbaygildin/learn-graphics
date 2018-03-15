//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_COLORBALANCE_H
#define OPENGL_COLORBALANCE_H


#include <QOpenGLShaderProgram>

class ColorBalance : public QOpenGLShaderProgram {
public:
    ColorBalance();

private:
    static constexpr auto VERTEX_PATH = "data/shaders/vertex.vert";
    static constexpr auto FRAG_PATH = "data/shaders/colorBalance.frag";
};


#endif //OPENGL_COLORBALANCE_H
