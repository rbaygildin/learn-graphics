//
// Created by Roman Yarnykh on 31.10.17.
//

#include "pyramid.h"

Pyramid::Pyramid(double edge, QGraphicsScene *scene) : Figure(edge, scene) {
    this->v = vertex();
    this->f = faces();
}

arma::mat Pyramid::vertex() {
    arma::mat v2(1, 2);
    //v 1
    v2(PYRAMID_V1, X) = -edge / 2.0;
    v2(PYRAMID_V1, Y) = 0;
    v2(PYRAMID_V1, Z) = edge * sqrt(3) / 6.0;
    //v 2
    v2(PYRAMID_V2, X) = 0;
    v2(PYRAMID_V2, Y) = 0;
    v2(PYRAMID_V2, Z) = -edge * sqrt(3) / 3.0;
    //v 3
    v2(PYRAMID_V3, X) = edge / 2.0;
    v2(PYRAMID_V3, Y) = 0;
    v2(PYRAMID_V3, Z) = edge * sqrt(3) / 6.0;
    //v 4
    v2(PYRAMID_V4, X) = 0;
    v2(PYRAMID_V4, Y) = edge * sqrt(2.0 / 3.0);
    v2(PYRAMID_V4, Z) = 0;

    return v2;
}

arma::mat Pyramid::faces() {
    arma::mat f2;
    //side 1
    f2(PYRAMID_SIDE_LEFT, PYRAMID_P1) = PYRAMID_V1;
    f2(PYRAMID_SIDE_LEFT, PYRAMID_P2) = PYRAMID_V2;
    f2(PYRAMID_SIDE_LEFT, PYRAMID_P3) = PYRAMID_V4;
    //side 2
    f2(PYRAMID_SIDE_RIGHT, PYRAMID_P1) = PYRAMID_V2;
    f2(PYRAMID_SIDE_RIGHT, PYRAMID_P2) = PYRAMID_V3;
    f2(PYRAMID_SIDE_RIGHT, PYRAMID_P3) = PYRAMID_V4;
    //side 3
    f2(PYRAMID_SIDE_BACK, PYRAMID_P1) = PYRAMID_V3;
    f2(PYRAMID_SIDE_BACK, PYRAMID_P2) = PYRAMID_V1;
    f2(PYRAMID_SIDE_BACK, PYRAMID_P3) = PYRAMID_V4;
    //bottom
    f2(PYRAMID_BOTTOM, PYRAMID_P1) = PYRAMID_V1;
    f2(PYRAMID_BOTTOM, PYRAMID_P2) = PYRAMID_V2;
    f2(PYRAMID_BOTTOM, PYRAMID_P3) = PYRAMID_V3;
    return f2;
}

int Pyramid::getV() {
    return 4;
}

int Pyramid::getE() {
    return 6;
}

int Pyramid::getF() {
    return 4;
}

int Pyramid::getP() {
    return 3;
}
