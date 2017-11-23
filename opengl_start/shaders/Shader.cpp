//
// Created by Max Heartfield on 22.11.17.
//

#include "Shader.h"

Shader::~Shader() {
    glDeleteShader(vertexId);
    glDeleteShader(fragId);
}

string Shader::readFile(const string &filePath) {
    ifstream f(filePath);
    BOOST_LOG_TRIVIAL(info) << "Shader file " << filePath << " was opened";
    stringstream s;
    s << f.rdbuf();
    BOOST_LOG_TRIVIAL(info) << "Shader file " << filePath << " was read";
    f.close();
    return s.str();
}

Shader::Shader(const string &vertexPath, const string &fragPath, GLuint program) {
    //Vertex shader
    vertexId = glCreateShader(GL_VERTEX_SHADER);
    string vs = readFile(vertexPath);
    const char *vsSource = vs.c_str();
    auto vsLen = static_cast<GLint>(vs.length());
    glShaderSource(vertexId, 1, &vsSource, &vsLen);
    GLint success = 0;
    BOOST_LOG_TRIVIAL(info) << "Compiling vertex shader...";
    glCompileShader(vertexId);
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        BOOST_LOG_TRIVIAL(fatal) << "Compilation vertex shader failed!";
        exit(EXIT_FAILURE);
    }
    glAttachShader(program, vertexId);

    //Frag shader
    fragId = glCreateShader(GL_FRAGMENT_SHADER);
    string fs = readFile(fragPath);
    const char *fsSource = fs.c_str();
    auto fsLen = static_cast<GLint>(fs.length());
    glShaderSource(fragId, 1, &fsSource, &fsLen);
    BOOST_LOG_TRIVIAL(info) << "Compilation fragment shader...";
    glCompileShader(fragId);
    glGetShaderiv(fragId, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        BOOST_LOG_TRIVIAL(fatal) << "Compilation frag shader failed!";
        exit(EXIT_FAILURE);
    }
    glAttachShader(program, fragId);
}
