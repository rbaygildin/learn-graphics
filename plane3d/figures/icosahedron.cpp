//
// Created by Roman Yarnykh on 01.11.17.
//

#include "icosahedron.h"

Icosahedron::Icosahedron(double edge, QGraphicsScene *scene) : Figure(edge, scene, 12, 30, 20, 3) {
    this->v = vertex();
    this->f = faces();
}

arma::mat Icosahedron::vertex() {
    arma::mat v2(static_cast<const arma::uword>(V), 3);
    double R = edge * sqrt(3.0) * (3.0 + sqrt(5.0)) / 12.0;
    double r = edge / (2.0 * sin(PI / 5.0));
    double alpha = acos((1 - edge * edge / 2 / R / R));
    double h = sqrt(abs(R * R - r * r));
    //top
    v2(ICOS_TOP, X) = 0;
    v2(ICOS_TOP, Y) = R;
    v2(ICOS_TOP, Z) = 0;
    //others
    for(int i = 0; i < 5; i++){
        //top
        v2(ICOS_TOP_V1 + i, X) = r * cos(PI/2 + 2.0 * PI * i / 5.0);
        v2(ICOS_TOP_V1 + i, Y) = h;
        v2(ICOS_TOP_V1 + i, Z) = r * sin(PI/2 + 2.0 * PI * i / 5.0);
        //bottom
        v2(ICOS_BOTTOM_V1 + i, X) = r * cos(PI/2 + 2.0 * PI * i / 5.0);
        v2(ICOS_BOTTOM_V1 + i, Y) = -h;
        v2(ICOS_BOTTOM_V1 + i, Z) = -r * sin(PI/2 + 2.0 * PI * i / 5.0);
    }
    //bottom
    v2(ICOS_BOTTOM, X) = 0;
    v2(ICOS_BOTTOM, Y) = -R;
    v2(ICOS_BOTTOM, Z) = 0;
    return v2;
}

arma::mat Icosahedron::faces() {
    arma::mat f2(static_cast<const arma::uword>(F), 3);

    //top
    f2(0, X) = ICOS_TOP_V1;
    f2(0, Y) = ICOS_TOP_V2;
    f2(0, Z) = ICOS_TOP;

    f2(1, X) = ICOS_TOP_V2;
    f2(1, Y) = ICOS_TOP_V3;
    f2(1, Z) = ICOS_TOP;

    f2(2, X) = ICOS_TOP_V3;
    f2(2, Y) = ICOS_TOP_V4;
    f2(2, Z) = ICOS_TOP;

    f2(3, X) = ICOS_TOP_V4;
    f2(3, Y) = ICOS_TOP_V5;
    f2(3, Z) = ICOS_TOP;

    f2(4, X) = ICOS_TOP_V5;
    f2(4, Y) = ICOS_TOP_V1;
    f2(4, Z) = ICOS_TOP;

    //bottom
    f2(5, X) = ICOS_BOTTOM_V1;
    f2(5, Y) = ICOS_BOTTOM_V2;
    f2(5, Z) = ICOS_BOTTOM;

    f2(6, X) = ICOS_BOTTOM_V2;
    f2(6, Y) = ICOS_BOTTOM_V3;
    f2(6, Z) = ICOS_BOTTOM;

    f2(7, X) = ICOS_BOTTOM_V3;
    f2(7, Y) = ICOS_BOTTOM_V4;
    f2(7, Z) = ICOS_BOTTOM;

    f2(8, X) = ICOS_BOTTOM_V4;
    f2(8, Y) = ICOS_BOTTOM_V5;
    f2(8, Z) = ICOS_BOTTOM;

    f2(9, X) = ICOS_BOTTOM_V5;
    f2(9, Y) = ICOS_BOTTOM_V1;
    f2(9, Z) = ICOS_BOTTOM;

    //front
    f2(10, X) = ICOS_TOP_V2;
    f2(10, Z) = ICOS_BOTTOM_V2;
    f2(10, Y) = ICOS_TOP_V3;
//
    f2(11, X) = ICOS_BOTTOM_V2;
    f2(11, Z) = ICOS_TOP_V3;
    f2(11, Y) = ICOS_BOTTOM_V1;
//
    f2(12, X) = ICOS_TOP_V3;
    f2(12, Y) = ICOS_BOTTOM_V1;
    f2(12, Z) = ICOS_TOP_V4;
//
    f2(13, Z) = ICOS_BOTTOM_V1;
    f2(13, X) = ICOS_TOP_V4;
    f2(13, Y) = ICOS_BOTTOM_V5;
//
    f2(14, X) = ICOS_TOP_V4;
    f2(14, Z) = ICOS_BOTTOM_V5;
    f2(14, Y) = ICOS_TOP_V5;
//
    f2(15, Z) = ICOS_BOTTOM_V5;
    f2(15, X) = ICOS_TOP_V5;
    f2(15, Y) = ICOS_BOTTOM_V4;
//
    f2(16, X) = ICOS_TOP_V5;
    f2(16, Z) = ICOS_BOTTOM_V4;
    f2(16, Y) = ICOS_TOP_V1;
//
    f2(17, X) = ICOS_BOTTOM_V4;
    f2(17, Z) = ICOS_TOP_V1;
    f2(17, Y) = ICOS_BOTTOM_V3;
//
    f2(18, X) = ICOS_TOP_V1;
    f2(18, Y) = ICOS_BOTTOM_V3;
    f2(18, Z) = ICOS_TOP_V2;
//
    f2(19, X) = ICOS_BOTTOM_V3;
    f2(19, Y) = ICOS_TOP_V2;
    f2(19, Z) = ICOS_BOTTOM_V2;
    return f2;
}

