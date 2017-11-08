//
// Created by Roman Yarnykh on 31.10.17.
//

#include <QJsonObject>
#include "pyramid.h"

Pyramid::Pyramid(double edge, QGraphicsScene *scene) : Figure(edge, scene) {
    this->originalV = vertex();
    this->f = faces();
    this->v = this->originalV;
    xC = 0;
    yC = 0;
    zC = 0;
    for(int i = 0; i < PYRAMID_V; i++){
        xC += v(0, i);
        yC += v(1, i);
        zC += v(2, i);
    }
    xC /= PYRAMID_V;
    yC /= PYRAMID_V;
    zC /= PYRAMID_V;
}

QGenericMatrix<PYRAMID_V, 3, qreal> Pyramid::vertex() {
    QGenericMatrix<PYRAMID_V, 3, qreal> v2;
    //v 1
    v2(X, PYRAMID_V1) = -this->edge / 2.0;
    v2(Y, PYRAMID_V1) = 0;
    v2(Z, PYRAMID_V1) = this->edge * sqrt(3) / 6.0;
    //v 2
    v2(X, PYRAMID_V2) = 0;
    v2(Y, PYRAMID_V2) = 0;
    v2(Z, PYRAMID_V2) = -this->edge * sqrt(3) / 3.0;
    //v 3
    v2(X, PYRAMID_V3) = this->edge / 2.0;
    v2(Y, PYRAMID_V3) = 0;
    v2(Z, PYRAMID_V3) = this->edge * sqrt(3) / 6.0;
    //v 4
    v2(X, PYRAMID_V4) = 0;
    v2(Y, PYRAMID_V4) = this->edge * sqrt(2.0 / 3.0);
    v2(Z, PYRAMID_V4) = 0;

    return v2;
}

QGenericMatrix<PYRAMID_F, PYRAMID_P, qreal> Pyramid::faces() {
    QGenericMatrix<PYRAMID_F, PYRAMID_P, qreal> f2;
    //side 1
    f2(PYRAMID_P1, PYRAMID_SIDE_LEFT) = PYRAMID_V1;
    f2(PYRAMID_P2, PYRAMID_SIDE_LEFT) = PYRAMID_V2;
    f2(PYRAMID_P3, PYRAMID_SIDE_LEFT) = PYRAMID_V4;
    //side 2
    f2(PYRAMID_P1, PYRAMID_SIDE_RIGHT) = PYRAMID_V2;
    f2(PYRAMID_P2, PYRAMID_SIDE_RIGHT) = PYRAMID_V3;
    f2(PYRAMID_P3, PYRAMID_SIDE_RIGHT) = PYRAMID_V4;
    //side 3
    f2(PYRAMID_P1, PYRAMID_SIDE_BACK) = PYRAMID_V3;
    f2(PYRAMID_P2, PYRAMID_SIDE_BACK) = PYRAMID_V1;
    f2(PYRAMID_P3, PYRAMID_SIDE_BACK) = PYRAMID_V4;
    //bottom
    f2(PYRAMID_P1, PYRAMID_BOTTOM) = PYRAMID_V1;
    f2(PYRAMID_P2, PYRAMID_BOTTOM) = PYRAMID_V2;
    f2(PYRAMID_P3, PYRAMID_BOTTOM) = PYRAMID_V3;
    return f2;
}

QRectF Pyramid::bound() {
    return QRectF(QPointF(originalV(0, PYRAMID_V1), originalV(1, PYRAMID_V4)), QPointF(originalV(0, PYRAMID_V3), originalV(1, PYRAMID_V3)));
}

QJsonObject Pyramid::toJson() {
    QJsonObject json = Figure::toJson();
    json.insert("type", "PYRAMID");
    return json;
}
