//
// Created by Max Heartfield on 22.11.17.
//

#include "Shader.h"

void Shader::attach() {
    glAttachShader(program, shaderId);
}

Shader::~Shader() {
    glDeleteShader(shaderId);
}

void Shader::detach() {
    glDetachShader(program, shaderId);
}

string Shader::readFile(const string &filePath) {
    ifstream f(filePath);
    stringstream s;
    s << f.rdbuf();
    f.close();
    return s.str();
}

Shader::Shader(const string &filePath, GLuint program) {

}
