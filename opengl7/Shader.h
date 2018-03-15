//
// Created by Max Heartfield on 13.03.18.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H


#include <QOpenGLFunctions>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include<string>

using namespace std;

class Shader : protected QOpenGLFunctions{
public:
    Shader(const QString &vertexFileName, const QString &fragmentFileName);

private:
    QString readFile(QString fileName);

    GLuint vertexId, fragmentId;
    GLuint programId;
};


#endif //OPENGL_SHADER_H
