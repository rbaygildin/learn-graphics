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

#include <boost/log/trivial.hpp>

using namespace std;

class Shader {
public:
    explicit Shader(const string &vertexPath, const string &fragPath, GLuint program);

    virtual ~Shader();

protected:
    string readFile(const string &filePath);

    GLuint vertexId;
    GLuint fragId;
    GLuint program;
};


#endif //OPENGL_START_SHADER_H
