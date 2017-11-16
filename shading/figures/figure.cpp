//
// Created by Max Heartfield on 14.11.17.
//

#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>
#include <utility>
#include "figure.h"

Figure::Figure(QObject *parent) : QObject(parent) {
    transformations[ScaleX] = 1.0;
    transformations[ScaleY] = 1.0;
    transformations[ScaleZ] = 1.0;
    transformations[RotateX] = 0.0;
    transformations[RotateY] = 0.0;
    transformations[RotateZ] = 0.0;
    transformations[TranslateX] = 0.0;
    transformations[TranslateY] = 0.0;
    transformations[TranslateZ] = 0.0;
}

Figure::~Figure() {

}

void Figure::transform(int operation, double value) {
    transformations[operation] = value;
}

void Figure::identityTransform() {
    transformations[ScaleX] = 1.0;
    transformations[ScaleY] = 1.0;
    transformations[ScaleZ] = 1.0;
    transformations[RotateX] = 0.0;
    transformations[RotateY] = 0.0;
    transformations[RotateZ] = 0.0;
    transformations[TranslateX] = 0.0;
    transformations[TranslateY] = 0.0;
    transformations[TranslateZ] = 0.0;
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    isChosen ^= true;
    qDebug() << "Figure clicked";
    QGraphicsItem::mousePressEvent(event);
}

void Figure::setLightingOptions(const QColor &color, double ia, double ka, double id, double kd, QVector3D lamp) {
    this->color = color;
    this->ia = ia;
    this->ka = ka;
    this->id = id;
    this->kd = kd;
    this->lamp = lamp;
}

QColor Figure::shade(QVector3D n) {
    double cos_ = QVector3D::dotProduct(n, lamp);
    double ambient = ia * ka;
    double diffuse = id * kd * cos_;
    double i = ambient + diffuse;
    i = i > 1 ? 1 : (i < 0 ? 0 : i);
    return QColor::fromRgbF(color.redF() * i, color.greenF() * i, color.blueF() * i, 1.0);
}

void Figure::setMeshMode() {
    mode = MESH;
}

void Figure::setWithLightingMode() {
    mode = WITH_LIGHTING;
}

void Figure::changeColor(QColor color) {
    this->color = std::move(color);
    scene()->update();
}

void Figure::changeAmbient(int tick) {
    this->ia = tick / 5.0 + 1;
    scene()->update();
}

void Figure::changeDiffuse(int tick) {
    this->id = tick / 5.0 + 1;
    scene()->update();
}

void Figure::changeLampX(int tick) {
    qDebug() << "Lamp x = " << tick;
    lamp.setX(tick - 50);
    scene()->update();
}

void Figure::changeLampY(int tick) {
    lamp.setY(tick - 50);
    scene()->update();
}

void Figure::changeLampZ(int tick) {
    lamp.setZ(tick - 50);
    scene()->update();
}

void Figure::changeKa(int tick) {
    ka = tick * 1.0 / 100.0;
    scene()->update();
}

void Figure::changeKd(int tick) {
    kd = tick * 1.0 / 100.0;
    scene()->update();
}

void Figure::changeKs(int tick) {
    ks = tick * 1.0 / 100;
}

void Figure::changeN(int tick) {
    n = tick / 10 + 1;
    scene()->update();
}
