//
// Created by Max Heartfield on 13.03.18.
//

#include "Shader.h"

Shader::Shader(const QString &vertexFileName, const QString &fragmentFileName) {
    initializeOpenGLFunctions();
    vertexId = glCreateShader(GL_VERTEX_SHADER);
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    auto source = readFile(vertexFileName);
    auto len = source.length();
    auto sourceChars = source.toStdString().c_str();
    glShaderSource(vertexId, len, &sourceChars, nullptr);
    glCompileShader(vertexId);

    GLint status = GL_FALSE;
    int messageLen;

    // Выполняем проверку Вершинного шейдера
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &status);
    glGetShaderiv(vertexId, GL_INFO_LOG_LENGTH, &messageLen);
    if (!status && messageLen > 0) {
        std::vector<char> message(static_cast<unsigned long>(messageLen + 1));
        glGetShaderInfoLog(vertexId, messageLen, nullptr, &message[0]);
        string s(message.begin(), message.end());
        qDebug() << QString::fromStdString(s);
        exit(-1);
    }

    source = readFile(fragmentFileName);
    len = source.length();
    sourceChars = source.toStdString().c_str();
    glShaderSource(fragmentId, len, &sourceChars, nullptr);
    glCompileShader(fragmentId);

    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &status);
    glGetShaderiv(fragmentId, GL_INFO_LOG_LENGTH, &messageLen);
    if (!status && messageLen > 0) {
        std::vector<char> message(static_cast<unsigned long>(messageLen + 1));
        glGetShaderInfoLog(fragmentId, messageLen, nullptr, &message[0]);
        string s(message.begin(), message.end());
        qDebug() << QString::fromStdString(s);
        exit(-1);
    }

    programId = glCreateProgram();
    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);
    glLinkProgram(programId);

    // Проверяем шейдерную программу
    glGetProgramiv(programId, GL_LINK_STATUS, &status);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &messageLen);

    if (messageLen > 0) {
        std::vector<char> message(static_cast<unsigned long>(messageLen + 1));
        glGetProgramInfoLog(programId, messageLen, nullptr, &message[0]);
        string s(message.begin(), message.end());
        qDebug() << QString::fromStdString(s);
        exit(-1);
    }

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

QString Shader::readFile(QString fileName) {
    QFile inputFile(fileName);
    QString res = "";
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            res += line + "\n";
        }
        inputFile.close();
    }
    return res;
}
