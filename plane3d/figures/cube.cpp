#include "cube.h"

Cube::Cube(double edge, QGraphicsScene *scene) : Figure(edge, scene, 8, 12, 6, 4)
{
    this->v = vertex();
    this->f = faces();
}

arma::mat Cube::vertex() {
    arma::mat v2(static_cast<const arma::uword>(V), 3);
    //v 1
    v2(V1, XC) = -edge / 2.0;
    v2(V1, YC) = 0;
    v2(V1, ZC) = -edge / 2.0;
    //v 2
    v2(V2, XC) = edge / 2.0;
    v2(V2, YC) = 0;
    v2(V2, ZC) = -edge / 2.0;
    //v 3
    v2(V3, XC) = edge / 2.0;
    v2(V3, YC) = 0;
    v2(V3, ZC) = edge / 2.0;
    //v 4
    v2(V4, XC) = -edge / 2.0;
    v2(V4, YC) = 0;
    v2(V4, ZC) = edge / 2.0;
    //v 5
    v2(V5, XC) = -edge / 2.0;
    v2(V5, YC) = edge;
    v2(V5, ZC) = -edge / 2.0;
    //v 6
    v2(V6, XC) = edge / 2.0;
    v2(V6, YC) = edge;
    v2(V6, ZC) = -edge / 2.0;
    //v 7
    v2(V7, XC) = edge / 2.0;
    v2(V7, YC) = edge;
    v2(V7, ZC) = edge / 2.0;
    //v 8
    v2(V8, XC) = -edge / 2.0;
    v2(V8, YC) = edge;
    v2(V8, ZC) = edge / 2.0;

    return v2;
}

arma::mat Cube::faces() {
    arma::mat f2(static_cast<const arma::uword>(F), static_cast<const arma::uword>(P));
    //side 1
    f2(SIDE_FRONT, P1) = V1;
    f2(SIDE_FRONT, P2) = V2;
    f2(SIDE_FRONT, P3) = V6;
    f2(SIDE_FRONT, P4) = V5;
    //side 2
    f2(SIDE_RIGHT, P1) = V2;
    f2(SIDE_RIGHT, P2) = V3;
    f2(SIDE_RIGHT, P3) = V7;
    f2(SIDE_RIGHT, P4) = V6;
    //side 3
    f2(SIDE_BACK, P1) = V3;
    f2(SIDE_BACK, P2) = V4;
    f2(SIDE_BACK, P3) = V8;
    f2(SIDE_BACK, P4) = V7;
    //side 4
    f2(SIDE_LEFT, P1) = V4;
    f2(SIDE_LEFT, P2) = V1;
    f2(SIDE_LEFT, P3) = V5;
    f2(SIDE_LEFT, P4) = V8;
    //top
    f2(TOP, P1) = V5;
    f2(TOP, P2) = V6;
    f2(TOP, P3) = V7;
    f2(TOP, P4) = V8;
    //bottom
    f2(BOTTOM, P1) = V1;
    f2(BOTTOM, P2) = V2;
    f2(BOTTOM, P3) = V3;
    f2(BOTTOM, P4) = V4;
    return f2;
}

