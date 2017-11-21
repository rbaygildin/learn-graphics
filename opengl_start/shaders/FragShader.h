//
// Created by Max Heartfield on 22.11.17.
//

#ifndef OPENGL_START_FRAGSHADER_H
#define OPENGL_START_FRAGSHADER_H


#include "Shader.h"

class FragShader : public Shader{
public:
    explicit FragShader(const string &filePath, GLuint program);

};


#endif //OPENGL_START_FRAGSHADER_H
