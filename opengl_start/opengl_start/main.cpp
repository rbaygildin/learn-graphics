//
//  main.cpp
//  opengl_start
//
//  Created by Roman Yarnykh on 12.11.17.
//  Copyright © 2017 Roman Yarnykh. All rights reserved.
//


#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

GLuint vertexes;
GLuint colors;

GLuint program;
GLuint vertexShader;
GLuint fragShader;

void loadShaders(const string&, const string&);
void createBuffers();
void display();
void deleteBuffers();
string readFile(const string&);

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("VBO");
    glutDisplayFunc(display);
    
    glMatrixMode(GL_MODELVIEW);
    
    createBuffers();
    loadShaders("shader.vert", "shader.frag");
    glutMainLoop();
    deleteBuffers();
    
    return 0;
}

string readFile(const string& path){
    ifstream f(path);
    stringstream s;
    s << f.rdbuf();
    f.close();
    return s.str();
}

void createBuffers() {
    static const GLfloat planeVertexes[4][3] = {
        {0.5, 0.5, 0.0},
        {-0.5, 0.5, 0.0},
        {-0.5, -0.5, 0.0},
        {0.5, -0.5, 0.0}
    };
    
    static const GLfloat planeColors[4][3] = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
        {1.0, 1.0, 1.0}
    };
    
    glGenBuffers(1, &vertexes);
    glGenBuffers(1, &colors);
    
    /* Vertex data */
    glBindBuffer(GL_ARRAY_BUFFER, vertexes);
    glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(GLfloat), planeVertexes, GL_STATIC_DRAW);
    
    /* Color data */
    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(GLfloat), planeColors, GL_STATIC_DRAW);
}

void loadShaders(const string &vertexShaderPath, const string &fragShaderPath){
    program = glCreateProgram();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    string vs = readFile(vertexShaderPath);
    string fs = readFile(fragShaderPath);
    const char* vsSoure = vs.c_str();
    const char *fsSource = fs.c_str();
    GLint vsLen = vs.length();
    GLint fsLen = fs.length();
    glShaderSource(vertexShader, 1, &vsSoure, &vsLen);
    glShaderSource(fragShader, 1, &fsSource, &fsLen);
    GLint success = 0;
    cout << "Compiling vertex shader" << endl;
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE){
        cout << "Compilation vertex shader failed!";
    }
    cout << "Compiling fragment shader" << endl;
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE){
        cout << "Compilation frag shader failed!";
    }
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
}

void display() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* Vertex data */
    glBindBuffer(GL_ARRAY_BUFFER, vertexes);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    /* Color data */
    glBindBuffer(GL_ARRAY_BUFFER, colors);
    glColorPointer(3, GL_FLOAT, 0, NULL);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glDrawArrays(GL_POLYGON, 0, 4);
    glFlush();
}

void deleteBuffers() {
    glDeleteBuffers(1, &vertexes);
    glDeleteBuffers(1, &colors);
}
