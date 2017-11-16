//
// Created by Max Heartfield on 15.11.17.
//

#ifndef PLANE3D_NONCONVEXFIGURE_H
#define PLANE3D_NONCONVEXFIGURE_H

#include "../../common.h"
#include "../../affine.h"
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
#include "../../point3d.h"
#include <cfloat>

using namespace std;

class NonConvexFigure : public Figure {
public
    functions:

    explicit NonConvexFigure(QObject *parent);

    ~NonConvexFigure() override;

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private functions:

    virtual std::vector<double> getCoords(ULONG row, ULONG c) = 0;

    virtual Matrix * vertices();

    Matrix applyTr();

protected functions:
    virtual QVector3D normal(QVector3D a, QVector3D b);
    virtual QColor flatShading(QColor color, double ia, double id, double ka, QVector3D n, QVector3D l);

    void paintMesh(QPainter *painter) override;

    void paintWithLighting(QPainter *painter) override;

    QColor flatShading(QVector3D a, QVector3D b);

    std::vector<std::vector<Point3D>> sortFaces();

protected fields:
    static const ULONG vCount = 50;
    static const ULONG hCount = 50;
    Matrix *vs = nullptr;
};


#endif //PLANE3D_NONCONVEXFIGURE_H
