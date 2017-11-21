//
// Created by Max Heartfield on 22.11.17.
//

#include "VertexShader.h"

VertexShader::VertexShader(const string &filePath, GLuint program) : Shader(filePath, program) {
    shaderId = glCreateShader(GL_VERTEX_SHADER);
    string vs = readFile(filePath);
    const char *vsSource = vs.c_str();
    auto vsLen = static_cast<GLint>(vs.length());
    glShaderSource(shaderId, 1, &vsSource, &vsLen);
    GLint success = 0;
    cout << "Compiling vertex shader" << endl;
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        cout << "Compilation vertex shader failed!";
    }
    glAttachShader(program, shaderId);
}
