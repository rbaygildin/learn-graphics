#ifndef TORUS_H
#define TORUS_H

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

class Torus : public NonConvexFigure {
public functions:

    explicit Torus(double R = 250, double r = 50, QObject *parent = nullptr);

    QJsonObject toJson() const override;

private functions:
    std::vector<double> getCoords(ULONG row, ULONG c) override;

private fields:
    double R, r;
};

#endif // TORUS_H
