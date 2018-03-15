//aberration.frag
// Created by Max Heartfield on 13.03.18.
//

#include "GLWidget.h"
#include "DicomUtils.h"
#include "Shader.h"
#include <cmath>
#include <GL/glut.h>
#include "utils.h"
#include "FiltersPool.h"

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define VERTEX_SHADER "data/shaders/vertex.vert"
#define FILTER1_SHADER "data/shaders/emboss.frag"
#define FILTER2_SHADER "data/shaders/abberation.frag"

#define vec2(x, y) (QVector2D(x, y))
#define vec3(x, y, z) (QVector3D(x, y, z))


GLWidget::GLWidget(const QWidget *parent) {

}

GLWidget::~GLWidget() = default;

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    makeObjects();
    makePrograms();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GLWidget::paintGL() {
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    QMatrix4x4 m;
    m.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 4.0f, 15.0f);
    m.translate(0.0f, 0.0f, -10.0f);
    m.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
    m.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
    m.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);

    currentFilter->bind();
    currentFilter->setUniformValue("matrix", m);
    currentFilter->setUniformValue("shift", shift);
    currentFilter->setUniformValue("shiftY", shiftY);
    currentFilter->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    currentFilter->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    currentFilter->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    currentFilter->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2,
                                      5 * sizeof(GLfloat));

    for (int i = 0; i < 6; ++i) {
        textures[i % 3]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }

    currentFilter->release();
    auto addFilter = FiltersPool::getInstance()->canny(0.3);
    addFilter->bind();
    addFilter->setUniformValue("matrix", m);
    addFilter->setUniformValue("shift", shift);
    addFilter->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    addFilter->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    addFilter->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    addFilter->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2,
                                  5 * sizeof(GLfloat));

    m.scale(0.5, 0.5, 0.5);
    m.translate(0.5f, 0.5f, 0.7f);
    addFilter->setUniformValue("matrix", m);

    for (int i = 0; i < 6; ++i) {
        textures[3 + i % 3]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }
    textures[3]->release();

//    addProgram->release();
//    mainProgram->bind();
//    m.scale(0.7, 0.7, 0.7);
//    m.translate(-0.5f, -0.2f, 0.2f);
//    mainProgram->setUniformValue("matrix", m);
//
//    textures[5]->bind();
//    for (int i = 0; i < 6; ++i) {
//        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
//    }
//    textures[5]->release();
//
//    glEnable(GL_COLOR_MATERIAL);
//    glBegin(GL_TRIANGLES);
//    {
//        glColor3f(1, 0, 0);
//        glVertex2f(-0.5f, 0.f);
//        glColor3f(0, 1, 0);
//        glVertex2f(0, 0.5f);
//        glColor3f(0, 0, 1);
//        glVertex2f(0.5f, 0);
//    }
//    glEnd();

    glFlush();
}

void GLWidget::resizeGL(int width, int height) {
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}

void GLWidget::rotateBy(int xAngle, int yAngle, int zAngle) {
    xRot += xAngle;
    yRot += yAngle;
    zRot += zAngle;
    update();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        rotateBy(8 * dy, 8 * dx, 0);
    } else if (event->buttons() & Qt::RightButton) {
        rotateBy(8 * dy, 0, 8 * dx);
    }
    lastPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {

}

void GLWidget::makeObjects() {
    static const int coords[6][4][3] = {
            {{+1, -1, -1}, {-1, -1, -1}, {-1, +1, -1}, {+1, +1, -1}},
            {{+1, +1, -1}, {-1, +1, -1}, {-1, +1, +1}, {+1, +1, +1}},
            {{+1, -1, +1}, {+1, -1, -1}, {+1, +1, -1}, {+1, +1, +1}},
            {{-1, -1, -1}, {-1, -1, +1}, {-1, +1, +1}, {-1, +1, -1}},
            {{+1, -1, +1}, {-1, -1, +1}, {-1, -1, -1}, {+1, -1, -1}},
            {{-1, -1, +1}, {+1, -1, +1}, {+1, +1, +1}, {-1, +1, +1}}
    };

    for (int j = 0; j < 6; ++j)
        textures[j] = new QOpenGLTexture(QImage(QString("data/pug.jpg")));
//    for (int j = 3; j < 5; ++j)
//        textures[j] = new QOpenGLTexture(QImage(QString("data/cameraman.jpg")));
//    textures[5] = new QOpenGLTexture();


    QVector<GLfloat> vertData;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 4; ++j) {
            // vertex position
            vertData.append(0.2 * coords[i][j][0]);
            vertData.append(0.2 * coords[i][j][1]);
            vertData.append(0.2 * coords[i][j][2]);
            // texture coordinate
            vertData.append(j == 0 || j == 3);
            vertData.append(j == 0 || j == 1);
        }
    }

    vbo.create();
    vbo.bind();
    vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}

void GLWidget::makePrograms() {

    if (currentFilter == nullptr) {
        currentFilter = FiltersPool::getInstance()->original();

//        currentFilter->addShaderFromSourceCode(QOpenGLShader::Vertex, readFile(VERTEX_SHADER));
//        currentFilter->addShaderFromSourceCode(QOpenGLShader::Fragment, readFile(FILTER1_SHADER));
//
//        currentFilter->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
//        currentFilter->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
//        currentFilter->link();
//        currentFilter->setUniformValueArray("kernel", new GLfloat[9]{
//                0.0625, 0.1250, 0.0625, 0.1250, 0.2500, 0.1250, 0.0625, 0.1250, 0.0625
//        }, 9, 1);
//        currentFilter->setUniformValueArray("offset", new QVector2D[9]{
//                vec2(-1.0f, -1.0f), vec2(0.0, -1.0f), vec2(1.0, -1.0f),
//                vec2(-1.0f, 0.0), vec2(0.0, 0.0), vec2(1.0, 0.0),
//                vec2(-1.0f, 1.0), vec2(0.0, 1.0), vec2(1.0, 1.0)
//        }, 9);
        currentFilter->setUniformValue("tex", 0);
    }
}

void GLWidget::drawSpehere(float x, float y, float z, float radius, long rings, long sectors) {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;

    float const R = 1. / (float) (rings - 1);
    float const S = 1. / (float) (sectors - 1);
    int r, s;

    vertices.resize(rings * sectors * 3);
    normals.resize(rings * sectors * 3);
    texcoords.resize(rings * sectors * 2);
    std::vector<GLfloat>::iterator v = vertices.begin();
    std::vector<GLfloat>::iterator n = normals.begin();
    std::vector<GLfloat>::iterator t = texcoords.begin();
    for (r = 0; r < rings; r++)
        for (s = 0; s < sectors; s++) {
            float const y = sin(-M_PI_2 + M_PI * r * R);
            float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

            *t++ = s * S;
            *t++ = r * R;

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;

            *n++ = x;
            *n++ = y;
            *n++ = z;
        }

    indices.resize(rings * sectors * 4);
    std::vector<GLushort>::iterator i = indices.begin();
    for (r = 0; r < rings; r++)
        for (s = 0; s < sectors; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s + 1);
            *i++ = (r + 1) * sectors + (s + 1);
            *i++ = (r + 1) * sectors + s;
        }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(x, y, z);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normals[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
    glDrawElements(GL_QUADS, indices.size() / 4, GL_UNSIGNED_SHORT, &indices[0]);
    glPopMatrix();
}

void GLWidget::setCurrentFilter(QOpenGLShaderProgram *filter) {
    this->currentFilter = filter;
    update();
}

void GLWidget::setCurrentTexture(const QStringList &fileNames) {
    if (fileNames.length() == 0)
        return;
    for (int j = 0; j < 6; ++j) {
        qDebug() << fileNames.length();
        auto fileName = fileNames[j % fileNames.length()];
        if (fileName.endsWith(".dcm")) {
            textures[j] = new QOpenGLTexture(DicomUtils::fromDicomFile(fileName));
        } else {
            textures[j] = new QOpenGLTexture(QImage(fileName));
        }
    }
    update();
}

void GLWidget::setShift(float shift, float shiftY) {
    this->shift = shift;
    this->shiftY = shiftY;
    update();
}
