//
// Created by Max Heartfield on 22.11.17.
//

#ifndef OPENGL_START_SHADER_H
#define OPENGL_START_SHADER_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
public:
    explicit Shader(const string &filePath, GLuint program);
    virtual void attach();
    virtual void detach();
    virtual ~Shader();

protected:
    string readFile(const string& filePath);
    GLuint shaderId;
    GLuint program;
};


#endif //OPENGL_START_SHADER_H
