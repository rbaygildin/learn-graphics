//
// Created by Max Heartfield on 13.03.18.
//

#ifndef OPENGL_GLWIDGET_H
#define OPENGL_GLWIDGET_H

#include <QOpenGLWidget>
#include <QObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QGLFormat>
#include <QGLContext>
#include <QWindow>

/**
 * GL context
 */
class GLWidget : public QOpenGLWidget, QOpenGLFunctions {
Q_OBJECT
public:
    explicit GLWidget(const QWidget *parent = nullptr);

    ~GLWidget() override;

public:
    void setCurrentFilter(QOpenGLShaderProgram *filter);
    void setCurrentTexture(const QStringList &fileNames);
    void setShift(float shift, float shiftY = 0);


public:
    /*
     * Rotate image
     */
    void rotateBy(int xAngle, int yAngle, int zAngle);

protected:
    /*
     * Init GL context
     *
     */
    void initializeGL() override;

    void paintGL() override;

    void resizeGL(int, int);

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void makeObjects();

    void makePrograms();

private:
    QOpenGLShaderProgram *currentFilter = nullptr;
    QColor clearColor;
    QPoint lastPos;
    int xRot;
    int yRot;
    int zRot;
    QOpenGLTexture *textures[6];
    QOpenGLBuffer vbo;
    QOpenGLContext *c;
    QOpenGLFunctions *gl;

    void drawSpehere(float x, float y, float z, float radius, long rings, long sectors);

    QOpenGLShaderProgram *addProgram;
    float shift;
    float shiftY;
};


#endif //OPENGL_GLWIDGET_H
