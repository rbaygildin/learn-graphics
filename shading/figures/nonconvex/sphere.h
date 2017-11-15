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
#include "../figure.h"
#include "nonconvex_figure.h"
#include <cfloat>

using namespace std;

class Sphere : public NonConvexFigure {
public functions:

    explicit Sphere(double R = 100, QObject *parent = nullptr);

    QJsonObject toJson() const override;

private functions:

    std::vector<double> getCoords(ULONG row, ULONG c);

private fields:
    double R;
};


#endif //PLANE3D_SPHERE_H
