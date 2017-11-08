#include <QJsonObject>
#include "cube.h"

Cube::Cube(double edge, QGraphicsScene *scene) : Figure<8, 12, 6, 4>(edge, scene)
{
    this->v = vertex();
    this->f = faces();
    this->originalV = this->v;
}

QGenericMatrix<V, 3, qreal> Cube::vertex() {
    QGenericMatrix<8, 3, qreal> v2;
    //v 1
    v2(XC, V1) = -this->edge / 2.0;
    v2(YC, V1) = 0;
    v2(ZC, V1) = -this->edge / 2.0;
    //v 2
    v2(XC, V2) = this->edge / 2.0;
    v2(YC, V2) = 0;
    v2(ZC, V2) = -this->edge / 2.0;
    //v 3
    v2(XC, V3) = this->edge / 2.0;
    v2(YC, V3) = 0;
    v2(ZC, V3) = this->edge / 2.0;
    //v 4
    v2(XC, V4) = -this->edge / 2.0;
    v2(YC, V4) = 0;
    v2(ZC, V4) = this->edge / 2.0;
    //v 5
    v2(XC, V5) = -this->edge / 2.0;
    v2(YC, V5) = this->edge;
    v2(ZC, V5) = -this->edge / 2.0;
    //v 6
    v2(XC, V6) = this->edge / 2.0;
    v2(YC, V6) = this->edge;
    v2(ZC, V6) = -this->edge / 2.0;
    //v 7
    v2(XC, V7) = this->edge / 2.0;
    v2(YC, V7) = this->edge;
    v2(ZC, V7) = this->edge / 2.0;
    //v 8
    v2(XC, V8) = -this->edge / 2.0;
    v2(YC, V8) = this->edge;
    v2(ZC, V8) = this->edge / 2.0;

    return v2;
}

QGenericMatrix<F, P, qreal> Cube::faces() {
    QGenericMatrix<F, P, qreal> f2;
    //side 1
    f2(P1, SIDE_FRONT) = V1;
    f2(P2, SIDE_FRONT) = V2;
    f2(P3, SIDE_FRONT) = V6;
    f2(P4, SIDE_FRONT) = V5;
    //side 2
    f2(P1, SIDE_RIGHT) = V2;
    f2(P2, SIDE_RIGHT) = V3;
    f2(P3, SIDE_RIGHT) = V7;
    f2(P4, SIDE_RIGHT) = V6;
    //side 3
    f2(P1, SIDE_BACK) = V3;
    f2(P2, SIDE_BACK) = V4;
    f2(P3, SIDE_BACK) = V8;
    f2(P4, SIDE_BACK) = V7;
    //side 4
    f2(P1, SIDE_LEFT) = V4;
    f2(P2, SIDE_LEFT) = V1;
    f2(P3, SIDE_LEFT) = V5;
    f2(P4, SIDE_LEFT) = V8;
    //top
    f2(P1, TOP) = V5;
    f2(P2, TOP) = V6;
    f2(P3, TOP) = V7;
    f2(P4, TOP) = V8;
    //bottom
    f2(P1, BOTTOM) = V1;
    f2(P2, BOTTOM) = V2;
    f2(P3, BOTTOM) = V3;
    f2(P4, BOTTOM) = V4;
    return f2;
}

QRectF Cube::bound() {
    return QRectF(QPointF(v(XC, V5), v(YC, V5)), QPointF(v(XC, V2), v(YC, V2)));
}

QJsonObject Cube::toJson() {
    QJsonObject json;
    json.insert("type", "CUBE");
    json.insert("edge", edge);
    return json;
}
