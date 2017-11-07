//
// Created by Roman Yarnykh on 01.11.17.
//

#include "octahedron.h"

Octahedron::Octahedron(double edge, QGraphicsScene *scene) : Figure(edge, scene) {
    this->v = vertex();
    this->f = faces();
}

arma::mat Octahedron::vertex() {
    arma::mat v2;
    //v 1
    v2(OCT_V1, X) = -this->edge / 2.0;
    v2(OCT_V1, Y) = 0;
    v2(OCT_V1, Z) = -this->edge / 2.0;
    //v 2
    v2(OCT_V2, X) = this->edge / 2.0;
    v2(OCT_V2, Y) = 0;
    v2(OCT_V2, Z) = -this->edge / 2.0;
    //v 3
    v2(OCT_V3, X) = this->edge / 2.0;
    v2(OCT_V3, Y) = 0;
    v2(OCT_V3, Z) = this->edge / 2.0;
    //v 4
    v2(OCT_V4, X) = -this->edge / 2.0;
    v2(OCT_V4, Y) = 0;
    v2(OCT_V4, Z) = this->edge / 2.0;
    //v 5
    v2(OCT_V5, X) = 0;
    v2(OCT_V5, Y) = this->edge * sqrt(2) / 2;
    v2(OCT_V5, Z) = 0;
    //v 6
    v2(OCT_V6, X) = 0;
    v2(OCT_V6, Y) = -this->edge * sqrt(2) / 2;
    v2(OCT_V6, Z) = 0;

    return v2;
}

arma::mat Octahedron::faces() {
    arma::mat f2;
    //front top
    f2(OCT_FRONT_TOP, OCT_P1) = OCT_V1;
    f2(OCT_FRONT_TOP, OCT_P2) = OCT_V2;
    f2(OCT_FRONT_TOP, OCT_P3) = OCT_V5;
    //right top
    f2(OCT_SIDE_RIGHT_TOP, OCT_P1) = OCT_V2;
    f2(OCT_SIDE_RIGHT_TOP, OCT_P2) = OCT_V3;
    f2(OCT_SIDE_RIGHT_TOP, OCT_P3) = OCT_V5;
    //back top
    f2(OCT_SIDE_BACK_TOP, OCT_P1) = OCT_V3;
    f2(OCT_SIDE_BACK_TOP, OCT_P2) = OCT_V4;
    f2(OCT_SIDE_BACK_TOP, OCT_P3) = OCT_V5;
    //left top
    f2(OCT_SIDE_LEFT_TOP, OCT_P1) = OCT_V4;
    f2(OCT_SIDE_LEFT_TOP, OCT_P2) = OCT_V1;
    f2(OCT_SIDE_LEFT_TOP, OCT_P3) = OCT_V5;
    //front bottom
    f2(OCT_FRONT_BOTTOM, OCT_P1) = OCT_V1;
    f2(OCT_FRONT_BOTTOM, OCT_P2) = OCT_V2;
    f2(OCT_FRONT_BOTTOM, OCT_P3) = OCT_V6;
    //right bottom
    f2(OCT_SIDE_RIGHT_BOTTOM, OCT_P1) = OCT_V2;
    f2(OCT_SIDE_RIGHT_BOTTOM, OCT_P2) = OCT_V3;
    f2(OCT_SIDE_RIGHT_BOTTOM, OCT_P3) = OCT_V6;
    //back bottom
    f2(OCT_SIDE_BACK_BOTTOM, OCT_P1) = OCT_V3;
    f2(OCT_SIDE_BACK_BOTTOM, OCT_P2) = OCT_V4;
    f2(OCT_SIDE_BACK_BOTTOM, OCT_P3) = OCT_V6;
    //left bottom
    f2(OCT_SIDE_LEFT_BOTTOM, OCT_P1) = OCT_V4;
    f2(OCT_SIDE_LEFT_BOTTOM, OCT_P2) = OCT_V1;
    f2(OCT_SIDE_LEFT_BOTTOM, OCT_P3) = OCT_V6;
    return f2;
}

int Octahedron::getV() {
    return 6;
}

int Octahedron::getE() {
    return 12;
}

int Octahedron::getF() {
    return 8;
}

int Octahedron::getP() {
    return 3;
}
