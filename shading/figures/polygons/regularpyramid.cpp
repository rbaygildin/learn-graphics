#include "regularpyramid.h"

RegularPyramid::RegularPyramid() = default;

unsigned int RegularPyramid::getV() const {
    return 4;
}

unsigned int RegularPyramid::getE() const {
    return 6;
}

unsigned int RegularPyramid::getF() const {
    return 4;
}

unsigned int RegularPyramid::getP() const {
    return 3;
}

Matrix RegularPyramid::verteces() const {
    Matrix v(getV(), 3);
    //v 1
    v(V1, X) = -this->edge / 2.0;
    v(V1, Y) = 0;
    v(V1, Z) = this->edge * sqrt(3) / 6.0;
    //v 2
    v(V2, X) = 0;
    v(V2, Y) = 0;
    v(V2, Z) = -this->edge * sqrt(3) / 3.0;
    //v 3
    v(V3, X) = this->edge / 2.0;
    v(V3, Y) = 0;
    v(V3, Z) = this->edge * sqrt(3) / 6.0;
    //v 4
    v(V4, X) = 0;
    v(V4, Y) = this->edge * sqrt(2.0 / 3.0);
    v(V4, Z) = 0;
    return v;
}

IntMatrix RegularPyramid::faces() const {
    IntMatrix f2(getF(), getP());
    //side 1
    f2(LEFT, P1) = V1;
    f2(LEFT, P2) = V2;
    f2(LEFT, P3) = V4;
    //side 2
    f2(RIGHT, P1) = V2;
    f2(RIGHT, P2) = V3;
    f2(RIGHT, P3) = V4;
    //side 3
    f2(BACK, P1) = V3;
    f2(BACK, P2) = V1;
    f2(BACK, P3) = V4;
    //bottom
    f2(BOTTOM, P1) = V1;
    f2(BOTTOM, P2) = V2;
    f2(BOTTOM, P3) = V3;
    return f2;
}
