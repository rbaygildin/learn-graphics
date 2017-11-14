//
//  main.cpp
//  opengl_start
//
//  Created by Roman Yarnykh on 12.11.17.
//  Copyright © 2017 Roman Yarnykh. All rights reserved.
//


/**
 1. Реализация рисования 3d фигур на 2d плоскости
 2. Вращение
 3. Перемещение
 **/

#include <stdio.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <OpenGL/glu.h>
#include <cstdlib>

#define KEY_ESCAPE 27
#define KEY_UP 38
#define KEY_DOWN 40
#define V2C(V) ((V.x)(,) (V.y)(,) (V.z))

typedef struct {
    int width;
    int height;
    char* title;
    
    float field_of_view_angle;
    float z_near;
    float z_far;
} glutWindow;

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} vertex;

glutWindow win;

float alpha = 0.0;
float deltaAngle = 0.0f;
float cameraAlpaha = 45.0f;

int mouseOldX = 0;
int mouseOldY = 0;
float zNear = 1.0f;
float zFar = 500.f;

int ww;
int wh;

vertex rot;

void changeSize(int w, int h){
    ww = w;
    wh = h;
    if(wh == 0)
        wh = 1.0;
    float ratio = ww * 1.0 / wh;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(cameraAlpaha, ratio, zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
}

void drawPyramid(){
    vertex A;
    A.x = -1.0f;
    A.y = 0.0f;
    A.z = -1.0f;
    vertex B;
    B.x = 1.0f;
    B.y = 0.0f;
    B.z = 1.0f;
    vertex C;
    C.x = 1.0f;
    C.y = 0.0f;
    C.z = 1.0f;
    vertex D;
    D.x = -1.0f;
    D.y = 0.0f;
    D.z = 1.0f;
    vertex E;
    E.x = 0.0f;
    E.y = 1.5f;
    E.z = 0.0f;
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(rot.y, 0, 1, 0);
    glRotatef(rot.x, 1, 0, 0);
    
    glBegin(GL_TRIANGLES);
    {
        //front
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(A.x, A.y, A.z); //A
        glVertex3f(B.x, B.y, B.z); //B
        glVertex3f(E.x, E.y, E.z); //E
        //right
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(B.x, B.y, B.z); //B
        glVertex3f(C.x, C.y, C.z); //C
        glVertex3f(E.x, E.y, E.z);  //E
        //back
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(C.x, C.y, C.z); //C
        glVertex3f(D.x, D.y, D.z); //D
        glVertex3f(E.x, E.y, E.z); //E
        //left
        glColor3f(1.0f,1.0f,0.0f);
        glVertex3f(D.x, D.y, D.z); //D
        glVertex3f(A.x, A.y, A.z); //A
        glVertex3f(E.x, E.y, E.z); //E
        //bottom 1
        glColor3f(1.0f,0.0f,1.0f);
        glVertex3f(A.x, A.y, A.z); //A
        glVertex3f(D.x, D.y, D.z); //D
        glVertex3f(B.x, B.y, B.z); //B
        //bottom 2
        glVertex3f(B.x, B.y, B.z); //B
        glVertex3f(C.x, C.y, C.z); //C
        glVertex3f(D.x, D.y, D.z); //D
    }
    glEnd();
    
    glPopMatrix();
}

void drawCube(){
    //bottom
    vertex A;
    A.x = -1.0f;
    A.y = -1.5f;
    A.z = 1.0f;
    vertex B;
    B.x = 1.0f;
    B.y = -1.5f;
    B.z = 1.0f;
    vertex C;
    C.x = 1.0f;
    C.y = -1.5f;
    C.z = -1.0f;
    vertex D;
    D.x = -1.0f;
    D.y = -1.5f;
    D.z = -1.0f;
    
    glBegin(GL_QUADS);
    {
        //front
        glColor3f(1, 0, 0);
        glVertex3f(A.x, A.y + 1, A.z);
        glColor3f(0, 1, 0);
        glVertex3f(B.x, B.y + 1, B.z);
        glColor3f(0, 0, 1);
        glVertex3f(B.x, B.y, B.z);
        glColor3f(0, 1, 1);
        glVertex3f(A.x, A.y, A.z);
        //right
        glColor3f(1, 0, 0);
        glVertex3f(B.x, B.y + 1, B.z);
        glColor3f(0, 1, 0);
        glVertex3f(C.x, C.y + 1, C.z);
        glColor3f(0, 0, 1);
        glVertex3f(C.x, C.y, C.z);
        glColor3f(0, 1, 1);
        glVertex3f(B.x, B.y, B.z);
        //back
        glColor3f(1, 0, 0);
        glVertex3f(C.x, C.y, C.z);
        glColor3f(0, 1, 0);
        glVertex3f(D.x, D.y, D.z);
        glColor3f(0, 0, 1);
        glVertex3f(D.x, D.y + 1.0, D.z);
        glColor3f(0, 1, 1);
        glVertex3f(C.x, C.y + 1.0, C.z);
        //left
        glColor3f(1, 0, 0);
        glVertex3f(D.x, D.y + 1, D.z);
        glColor3f(0, 1, 0);
        glVertex3f(A.x, A.y + 1, A.z);
        glColor3f(0, 0, 1);
        glVertex3f(A.x, A.y, A.z);
        glColor3f(0, 1, 1);
        glVertex3f(D.x, D.y, D.z);
        //bottom
        glColor3f(1, 0, 0);
        glVertex3f(B.x, B.y, B.z);
        glColor3f(0, 1, 0);
        glVertex3f(C.x, C.y, C.z);
        glColor3f(0, 0, 1);
        glVertex3f(D.x, D.y, D.z);
        glColor3f(0, 1, 1);
        glVertex3f(A.x, A.y, A.z);
        //top
        glColor3f(1, 0, 0);
        glVertex3f(B.x, B.y + 1, B.z);
        glColor3f(0, 1, 0);
        glVertex3f(C.x, C.y + 1, C.z);
        glColor3f(0, 0, 1);
        glVertex3f(D.x, D.y + 1, D.z);
        glColor3f(0, 1, 1);
        glVertex3f(A.x, A.y + 1, A.z);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0f,0.0f,-3.0f);
    glRotatef(rot.y, 0, 1, 0);
    glRotatef(rot.x, 1, 0, 0);
    drawPyramid();
    drawCube();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            mouseOldX = x;
            mouseOldY = y;
        }
    }
}

void motion(int x, int y){
    rot.y -= ((mouseOldY - y) * 180.0f) / 200.0f;
    rot.x -= ((mouseOldX - x) * 180.0f) / 200.0f;
    rot.x  = 0;
    
    if ( rot.z > 360 )
        rot.z -= 360;
    
    if ( rot.z < -360 )
        rot.z += 360;
    
    if ( rot.y > 360 )
        rot.y -= 360;
    
    if ( rot.y < -360 )
        rot.y += 360;
    
    mouseOldX = x;
    mouseOldY = y;
    
    glutPostRedisplay ();
}

void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )
{
    switch ( key )
    {
        case KEY_ESCAPE:
            exit ( 0 );
            break;
            
        case KEY_UP:
            if(cameraAlpaha > 180.0f)
                cameraAlpaha = 0.0f;
            cameraAlpaha += 10.0f;
            glutPostRedisplay();
            break;
        
        case KEY_DOWN:
            if(cameraAlpaha < 0.0f)
                cameraAlpaha = 180.0f;
            cameraAlpaha -= 10.0f;
            glutPostRedisplay();
            break;
            
        default:
            break;
    }
}

int main(int argc, char **argv)
{
    // set window values
    win.width = 640;
    win.height = 480;
    win.field_of_view_angle = 45;
    win.z_near = 1.0f;
    win.z_far = 1500.0f;
    rot.x = 0.0f;
    rot.y = 0.0f;
    rot.z = 0.0f;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(win.width,win.height);
    glutCreateWindow("OpenGL Start");
    glutReshapeFunc(changeSize);
    glutDisplayFunc(display);
    glutIdleFunc( display );
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

