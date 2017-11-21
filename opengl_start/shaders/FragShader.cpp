//
// Created by Max Heartfield on 22.11.17.
//

#include "FragShader.h"

FragShader::FragShader(const string &filePath, GLuint program) : Shader(filePath, program) {
    shaderId = glCreateShader(GL_FRAGMENT_SHADER);
    string fs = readFile(filePath);
    const char *fsSource = fs.c_str();
    auto fsLen = static_cast<GLint>(fs.length());
    glShaderSource(shaderId, 1, &fsSource, &fsLen);
    GLint success = 0;
    cout << "Compiling fragment shader" << endl;
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        cout << "Compilation frag shader failed!";
    }
    glAttachShader(program, shaderId);
}
