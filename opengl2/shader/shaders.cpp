#include "../common.h"

#include "shaders.h"
#include "../logger.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader() {
    bLoaded = false;
}

Shader shShaders[NUMSHADERS];
ShaderProgram spMain, spColor;

// Loads all shaders and creates shader programs.
bool PrepareShaderPrograms() {
    // Load shaders and create shader program

    string sShaderFileNames[] = {"main_shader.vert", "main_shader.frag", "dirLight.frag",
                                 "color.vert", "color.frag"
    };

    FOR(i, NUMSHADERS)
    {
        string sExt = sShaderFileNames[i].substr(ESZ(sShaderFileNames[i]) - 4, 4);
        int iShaderType =
                sExt == "vert" ? GL_VERTEX_SHADER : (sExt == "frag" ? GL_FRAGMENT_SHADER : GL_GEOMETRY_SHADER);
        shShaders[i].LoadShader("data/shaders/" + sShaderFileNames[i], iShaderType);
    }

    // Create shader programs

    spMain.CreateProgram();
    spMain.AddShaderToProgram(&shShaders[0]);
    spMain.AddShaderToProgram(&shShaders[1]);
    spMain.AddShaderToProgram(&shShaders[2]);
    //spMain.AddShaderToProgram(&shShaders[3]);
    //spMain.AddShaderToProgram(&shShaders[6]);
    spMain.LinkProgram();

    if (!spMain.LinkProgram())return false;

    spColor.CreateProgram();
    spColor.AddShaderToProgram(&shShaders[3]);
    spColor.AddShaderToProgram(&shShaders[4]);
    //spColor.AddShaderToProgram(&shShaders[4]);
    //spColor.AddShaderToProgram(&shShaders[5]);
    spColor.LinkProgram();

    return true;
}

// Loads and compiles shader.
// sFile - path to a file
// a_iType - type of shader(fragment, vertex, geometry)
bool Shader::LoadShader(string sFile, int a_iType) {
    vector <string> sLines;

    if (!GetLinesFromFile(sFile, false, &sLines))return false;

    const char **sProgram = new const char *[ESZ(sLines)];
    FOR(i, ESZ(sLines))
    sProgram[i] = sLines[i].c_str();

    uiShader = glCreateShader(a_iType);

    glShaderSource(uiShader, ESZ(sLines), sProgram, NULL);
    glCompileShader(uiShader);

    delete[] sProgram;

    int iCompilationStatus;
    glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iCompilationStatus);

    if (iCompilationStatus == GL_FALSE) {
        char sInfoLog[1024];
        char sFinalMessage[1536];
        int iLogLength;
        glGetShaderInfoLog(uiShader, 1024, &iLogLength, sInfoLog);
        sprintf(sFinalMessage, "Error! Shader file %s wasn't compiled! The compiler returned:\n\n%s", sFile.c_str(),
                sInfoLog);
        Logger::error(sFinalMessage);
        return false;
    }
    iType = a_iType;
    bLoaded = true;

    return true;
}

// Loads and adds include part.
// sFile - path to a file
// bIncludePart - whether to add include part only
// vResult - vector of strings to store result to
bool Shader::GetLinesFromFile(string sFile, bool bIncludePart, vector <string> *vResult) {
    FILE *fp = fopen(sFile.c_str(), "rt");
    if (!fp)return false;

    string sDirectory;
    int slashIndex = -1;
    RFOR(i, ESZ(sFile) - 1)
    {
        if (sFile[i] == '/' || sFile[i] == '/') {
            slashIndex = i;
            break;
        }
    }

    sDirectory = sFile.substr(0, slashIndex + 1);

    // Get all lines from a file

    char sLine[255];

    bool bInIncludePart = false;

    while (fgets(sLine, 255, fp)) {
        stringstream ss(sLine);
        string sFirst;
        ss >> sFirst;
        if (sFirst == "#include") {
            string sFileName;
            ss >> sFileName;
            if (ESZ(sFileName) > 0 && sFileName[0] == '\"' && sFileName[ESZ(sFileName) - 1] == '\"') {
                sFileName = sFileName.substr(1, ESZ(sFileName) - 2);
                GetLinesFromFile(sDirectory + sFileName, true, vResult);
            }
        } else if (sFirst == "#include_part")
            bInIncludePart = true;
        else if (sFirst == "#definition_part")
            bInIncludePart = false;
        else if (!bIncludePart || (bIncludePart && bInIncludePart))
            vResult->push_back(sLine);
    }
    fclose(fp);

    return true;
}

// True if shader was loaded and compiled.
bool Shader::IsLoaded() {
    return bLoaded;
}

// Returns ID of a generated shader.
UINT Shader::GetShaderID() {
    return uiShader;
}

// Deletes shader and frees memory in GPU.
void Shader::DeleteShader() {
    if (!IsLoaded())return;
    bLoaded = false;
    glDeleteShader(uiShader);
}

ShaderProgram::ShaderProgram() {
    bLinked = false;
}

// Creates a new program.
void ShaderProgram::CreateProgram() {
    uiProgram = glCreateProgram();
}

// Adds a shader (like source file) to a program, but only compiled one.
// sShader - shader to add
bool ShaderProgram::AddShaderToProgram(Shader *shShader) {
    if (!shShader->IsLoaded())return false;

    glAttachShader(uiProgram, shShader->GetShaderID());

    return true;
}

// Performs final linkage of OpenGL program.
bool ShaderProgram::LinkProgram() {
    glLinkProgram(uiProgram);
    int iLinkStatus;
    glGetProgramiv(uiProgram, GL_LINK_STATUS, &iLinkStatus);
    bLinked = iLinkStatus == GL_TRUE;
    return bLinked;
}

// Deletes program and frees memory on GPU.
void ShaderProgram::DeleteProgram() {
    if (!bLinked)return;
    bLinked = false;
    glDeleteProgram(uiProgram);
}

// Tells OpenGL to use this program.
void ShaderProgram::UseProgram() {
    if (bLinked)glUseProgram(uiProgram);
}

// Returns OpenGL generated shader program ID.
UINT ShaderProgram::GetProgramID() {
    return uiProgram;
}

// These set of functions set most common types of uniform variables.

// Setting floats

void ShaderProgram::SetUniform(string sName, float *fValues, int iCount) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform1fv(iLoc, iCount, fValues);
}

void ShaderProgram::SetUniform(string sName, const float fValue) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform1fv(iLoc, 1, &fValue);
}

// Setting vectors

void ShaderProgram::SetUniform(string sName, glm::vec2 *vVectors, int iCount) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform2fv(iLoc, iCount, (GLfloat *) vVectors);
}

void ShaderProgram::SetUniform(string sName, const glm::vec2 vVector) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform2fv(iLoc, 1, (GLfloat * ) & vVector);
}

void ShaderProgram::SetUniform(string sName, glm::vec3 *vVectors, int iCount) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform3fv(iLoc, iCount, (GLfloat *) vVectors);
}

void ShaderProgram::SetUniform(string sName, const glm::vec3 vVector) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform3fv(iLoc, 1, (GLfloat * ) & vVector);
}

void ShaderProgram::SetUniform(string sName, glm::vec4 *vVectors, int iCount) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform4fv(iLoc, iCount, (GLfloat *) vVectors);
}

void ShaderProgram::SetUniform(string sName, const glm::vec4 &vVector) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform4fv(iLoc, 1, (GLfloat * ) & vVector);
}

// Setting 3x3 matrices

void ShaderProgram::SetUniform(string sName, glm::mat3 *mMatrices, int iCount) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniformMatrix3fv(iLoc, iCount, FALSE, (GLfloat *) mMatrices);
}

void ShaderProgram::SetUniform(string sName, const glm::mat3 mMatrix) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniformMatrix3fv(iLoc, 1, FALSE, (GLfloat * ) & mMatrix);
}

// Setting 4x4 matrices

void ShaderProgram::SetUniform(string sName, glm::mat4 *mMatrices, int iCount) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniformMatrix4fv(iLoc, iCount, FALSE, (GLfloat *) mMatrices);
}

void ShaderProgram::SetUniform(string sName, const glm::mat4 &mMatrix) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniformMatrix4fv(iLoc, 1, FALSE, (GLfloat * ) & mMatrix);
}

// Setting integers

void ShaderProgram::SetUniform(string sName, int *iValues, int iCount) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform1iv(iLoc, iCount, iValues);
}

void ShaderProgram::SetUniform(string sName, const int iValue) {
    int iLoc = glGetUniformLocation(uiProgram, sName.c_str());
    glUniform1i(iLoc, iValue);
}
