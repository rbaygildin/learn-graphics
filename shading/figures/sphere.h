//
// Created by Max Heartfield on 15.11.17.
//

#ifndef PLANE3D_SPHERE_H
#define PLANE3D_SPHERE_H


#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QRectF>
#include <QDebug>
#include <QVector3D>
#include "figure.h"
#include <cfloat>

using namespace std;

class Sphere : public Figure{
public functions:

    explicit Sphere(double R = 100, QObject *parent = nullptr);

    ~Sphere() override;

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QJsonObject toJson() const override;

private functions:
    std::vector<double> getCoords(ULONG row, ULONG c);
    Matrix applyTr();

private fields:
    static const ULONG vCount = 60;
    static const ULONG hCount = 60;
    double R;
    Matrix *vs;
};


#endif //PLANE3D_SPHERE_H
