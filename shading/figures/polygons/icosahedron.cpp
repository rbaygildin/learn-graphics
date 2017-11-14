#include "icosahedron.h"

Icosahedron::Icosahedron() = default;

unsigned int Icosahedron::getV() const {
    return 12;
}

unsigned int Icosahedron::getE() const {
    return 30;
}

unsigned int Icosahedron::getF() const {
    return 20;
}

unsigned int Icosahedron::getP() const {
    return 3;
}

Matrix Icosahedron::verteces() const {
    Matrix v(getV(), 3);
    double R = edge * sqrt(3.0) * (3.0 + sqrt(5.0)) / 12.0;
    double r = edge / (2.0 * sin(M_PI / 5.0));
    double alpha = acos((1 - edge * edge / 2 / R / R));
    double h = sqrt(abs(R * R - r * r));
    //top
    v(TOP, X) = 0;
    v(TOP, Y) = R;
    v(TOP, Z) = 0;
    //others
    for (int i = 0; i < 5; i++) {
        //top
        v(TOP_V1 + i, X) = r * cos(M_PI / 2 + 2.0 * M_PI * i / 5.0);
        v(TOP_V1 + i, Y) = h;
        v(TOP_V1 + i, Z) = r * sin(M_PI / 2 + 2.0 * M_PI * i / 5.0);
        //bottom
        v(BOTTOM_V1 + i, X) = r * cos(M_PI / 2 + 2.0 * M_PI * i / 5.0);
        v(BOTTOM_V1 + i, Y) = -h;
        v(BOTTOM_V1 + i, Z) = -r * sin(M_PI / 2 + 2.0 * M_PI * i / 5.0);
    }
    //bottom
    v(BOTTOM, X) = 0;
    v(BOTTOM, Y) = -R;
    v(BOTTOM, Z) = 0;
    return v;
}

IntMatrix Icosahedron::faces() const {
    IntMatrix f(getF(), getP());

    //top
    f(0, X) = TOP_V1;
    f(0, Y) = TOP_V2;
    f(0, Z) = TOP;

    f(1, X) = TOP_V2;
    f(1, Y) = TOP_V3;
    f(1, Z) = TOP;

    f(2, X) = TOP_V3;
    f(2, Y) = TOP_V4;
    f(2, Z) = TOP;

    f(3, X) = TOP_V4;
    f(3, Y) = TOP_V5;
    f(3, Z) = TOP;

    f(4, X) = TOP_V5;
    f(4, Y) = TOP_V1;
    f(4, Z) = TOP;

    //bottom
    f(5, X) = BOTTOM_V1;
    f(5, Y) = BOTTOM_V2;
    f(5, Z) = BOTTOM;

    f(6, X) = BOTTOM_V2;
    f(6, Y) = BOTTOM_V3;
    f(6, Z) = BOTTOM;

    f(7, X) = BOTTOM_V3;
    f(7, Y) = BOTTOM_V4;
    f(7, Z) = BOTTOM;

    f(8, X) = BOTTOM_V4;
    f(8, Y) = BOTTOM_V5;
    f(8, Z) = BOTTOM;

    f(9, X) = BOTTOM_V5;
    f(9, Y) = BOTTOM_V1;
    f(9, Z) = BOTTOM;
    
    //front
    f(10, X) = TOP_V2;
    f(10, Z) = BOTTOM_V2;
    f(10, Y) = TOP_V3;
//
    f(11, X) = BOTTOM_V2;
    f(11, Z) = TOP_V3;
    f(11, Y) = BOTTOM_V1;
//
    f(12, X) = TOP_V3;
    f(12, Y) = BOTTOM_V1;
    f(12, Z) = TOP_V4;
//
    f(13, Z) = BOTTOM_V1;
    f(13, X) = TOP_V4;
    f(13, Y) = BOTTOM_V5;
//
    f(14, X) = TOP_V4;
    f(14, Z) = BOTTOM_V5;
    f(14, Y) = TOP_V5;
//
    f(15, Z) = BOTTOM_V5;
    f(15, X) = TOP_V5;
    f(15, Y) = BOTTOM_V4;
//
    f(16, X) = TOP_V5;
    f(16, Z) = BOTTOM_V4;
    f(16, Y) = TOP_V1;
//
    f(17, X) = BOTTOM_V4;
    f(17, Z) = TOP_V1;
    f(17, Y) = BOTTOM_V3;
//
    f(18, X) = TOP_V1;
    f(18, Y) = BOTTOM_V3;
    f(18, Z) = TOP_V2;
//
    f(19, X) = BOTTOM_V3;
    f(19, Y) = TOP_V2;
    f(19, Z) = BOTTOM_V2;
    return f;
}
