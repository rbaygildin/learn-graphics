//
// Created by Roman Yarnykh on 01.11.17.
//

#include <QJsonObject>
#include "icosahedron.h"

Icosahedron::Icosahedron(double edge, QGraphicsScene *scene) : Figure(edge, scene) {
    this->originalV = vertex();
    this->f = faces();
    this->v = this->originalV;
    xC = 0;
    yC = 0;
    zC = 0;
    for(int i = 0; i < ICOS_V; i++){
        xC += v(0, i);
        yC += v(1, i);
        zC += v(2, i);
    }
    xC /= ICOS_V;
    yC /= ICOS_V;
    zC /= ICOS_V;
}

QGenericMatrix<ICOS_V, 3, qreal> Icosahedron::vertex() {
    QGenericMatrix<ICOS_V, 3, qreal> v2;
    double R = edge * sqrt(3.0) * (3.0 + sqrt(5.0)) / 12.0;
    double r = edge / (2.0 * sin(PI / 5.0));
    double alpha = acos((1 - edge * edge / 2 / R / R));
    double h = sqrt(abs(R * R - r * r));
    //top
    v2(X, ICOS_TOP) = 0;
    v2(Y, ICOS_TOP) = R;
    v2(Z, ICOS_TOP) = 0;
    //others
    for(int i = 0; i < 5; i++){
        //top
        v2(X, ICOS_TOP_V1 + i) = r * cos(PI/2 + 2.0 * PI * i / 5.0);
        v2(Y, ICOS_TOP_V1 + i) = h;
        v2(Z, ICOS_TOP_V1 + i) = r * sin(PI/2 + 2.0 * PI * i / 5.0);
        //bottom
        v2(X, ICOS_BOTTOM_V1 + i) = r * cos(PI/2 + 2.0 * PI * i / 5.0);
        v2(Y, ICOS_BOTTOM_V1 + i) = -h;
        v2(Z, ICOS_BOTTOM_V1 + i) = -r * sin(PI/2 + 2.0 * PI * i / 5.0);
    }
    //bottom
    v2(X, ICOS_BOTTOM) = 0;
    v2(Y, ICOS_BOTTOM) = -R;
    v2(Z, ICOS_BOTTOM) = 0;
    return v2;
}

QGenericMatrix<ICOS_F, ICOS_P, qreal> Icosahedron::faces() {
    QGenericMatrix<ICOS_F, ICOS_P, qreal> f2;

    //top
    f2(X, 0) = ICOS_TOP_V1;
    f2(Y, 0) = ICOS_TOP_V2;
    f2(Z, 0) = ICOS_TOP;

    f2(X, 1) = ICOS_TOP_V2;
    f2(Y, 1) = ICOS_TOP_V3;
    f2(Z, 1) = ICOS_TOP;

    f2(X, 2) = ICOS_TOP_V3;
    f2(Y, 2) = ICOS_TOP_V4;
    f2(Z, 2) = ICOS_TOP;

    f2(X, 3) = ICOS_TOP_V4;
    f2(Y, 3) = ICOS_TOP_V5;
    f2(Z, 3) = ICOS_TOP;

    f2(X, 4) = ICOS_TOP_V5;
    f2(Y, 4) = ICOS_TOP_V1;
    f2(Z, 4) = ICOS_TOP;

    //bottom
    f2(X, 5) = ICOS_BOTTOM_V1;
    f2(Y, 5) = ICOS_BOTTOM_V2;
    f2(Z, 5) = ICOS_BOTTOM;

    f2(X, 6) = ICOS_BOTTOM_V2;
    f2(Y, 6) = ICOS_BOTTOM_V3;
    f2(Z, 6) = ICOS_BOTTOM;

    f2(X, 7) = ICOS_BOTTOM_V3;
    f2(Y, 7) = ICOS_BOTTOM_V4;
    f2(Z, 7) = ICOS_BOTTOM;

    f2(X, 8) = ICOS_BOTTOM_V4;
    f2(Y, 8) = ICOS_BOTTOM_V5;
    f2(Z, 8) = ICOS_BOTTOM;

    f2(X, 9) = ICOS_BOTTOM_V5;
    f2(Y, 9) = ICOS_BOTTOM_V1;
    f2(Z, 9) = ICOS_BOTTOM;

    //front
    f2(X, 10) = ICOS_TOP_V2;
    f2(Z, 10) = ICOS_BOTTOM_V2;
    f2(Y, 10) = ICOS_TOP_V3;
//
    f2(X, 11) = ICOS_BOTTOM_V2;
    f2(Z, 11) = ICOS_TOP_V3;
    f2(Y, 11) = ICOS_BOTTOM_V1;
//
    f2(X, 12) = ICOS_TOP_V3;
    f2(Y, 12) = ICOS_BOTTOM_V1;
    f2(Z, 12) = ICOS_TOP_V4;
//
    f2(Z, 13) = ICOS_BOTTOM_V1;
    f2(X, 13) = ICOS_TOP_V4;
    f2(Y, 13) = ICOS_BOTTOM_V5;
//
    f2(X, 14) = ICOS_TOP_V4;
    f2(Z, 14) = ICOS_BOTTOM_V5;
    f2(Y, 14) = ICOS_TOP_V5;
//
    f2(Z, 15) = ICOS_BOTTOM_V5;
    f2(X, 15) = ICOS_TOP_V5;
    f2(Y, 15) = ICOS_BOTTOM_V4;
//
    f2(X, 16) = ICOS_TOP_V5;
    f2(Z, 16) = ICOS_BOTTOM_V4;
    f2(Y, 16) = ICOS_TOP_V1;
//
    f2(X, 17) = ICOS_BOTTOM_V4;
    f2(Z, 17) = ICOS_TOP_V1;
    f2(Y, 17) = ICOS_BOTTOM_V3;
//
    f2(X, 18) = ICOS_TOP_V1;
    f2(Y, 18) = ICOS_BOTTOM_V3;
    f2(Z, 18) = ICOS_TOP_V2;
//
    f2(X, 19) = ICOS_BOTTOM_V3;
    f2(Y, 19) = ICOS_TOP_V2;
    f2(Z, 19) = ICOS_BOTTOM_V2;
    return f2;
}

QRectF Icosahedron::bound() {
    return QRectF(QPointF(originalV(0, ICOS_TOP_V5), originalV(1, ICOS_TOP)), QPointF(originalV(0, ICOS_BOTTOM_V2), originalV(1, ICOS_BOTTOM)));
}

QJsonObject Icosahedron::toJson() {
    QJsonObject json = Figure::toJson();
    json.insert("type", "ICOSAHEDRON");
    return json;
}
