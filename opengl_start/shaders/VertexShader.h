//
// Created by Max Heartfield on 22.11.17.
//

#ifndef OPENGL_START_VERTEXSHADER_H
#define OPENGL_START_VERTEXSHADER_H


#include "Shader.h"

class VertexShader : public Shader{
public:
    explicit VertexShader(const string &filePath, GLuint program);

};


#endif //OPENGL_START_VERTEXSHADER_H
