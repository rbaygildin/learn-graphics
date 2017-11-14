#include "cube.h"

Cube::Cube(double edge, QVector3D center) : Polygon(edge, center){

}

unsigned int Cube::getV() const{
    return 8;
}

unsigned int Cube::getE() const{
    return 12;
}

unsigned int Cube::getF() const{
    return 6;
}

unsigned int Cube::getP() const{
    return 4;
}

Matrix Cube::vertices() const {
    Matrix v2(getV(), 3);
    //v 1
    v2(V1, X) = -this->edge / 2.0;
    v2(V1, Y) = 0;
    v2(V1, Z) = -this->edge / 2.0;
    //v 2
    v2(V2, X) = this->edge / 2.0;
    v2(V2, Y) = 0;
    v2(V2, Z) = -this->edge / 2.0;
    //v 3
    v2(V3, X) = this->edge / 2.0;
    v2(V3, Y) = 0;
    v2(V3, Z) = this->edge / 2.0;
    //v 4
    v2(V4, X) = -this->edge / 2.0;
    v2(V4, Y) = 0;
    v2(V4, Z) = this->edge / 2.0;
    //v 5
    v2(V5, X) = -this->edge / 2.0;
    v2(V5, Y) = this->edge;
    v2(V5, Z) = -this->edge / 2.0;
    //v 6
    v2(V6, X) = this->edge / 2.0;
    v2(V6, Y) = this->edge;
    v2(V6, Z) = -this->edge / 2.0;
    //v 7
    v2(V7, X) = this->edge / 2.0;
    v2(V7, Y) = this->edge;
    v2(V7, Z) = this->edge / 2.0;
    //v 8
    v2(V8, X) = -this->edge / 2.0;
    v2(V8, Y) = this->edge;
    v2(V8, Z) = this->edge / 2.0;

    return v2;
}

IntMatrix Cube::faces() const {
    Matrix f2(getF(), getP());
    //side 1
    f2(FRONT, P1) = V1;
    f2(FRONT, P2) = V2;
    f2(FRONT, P3) = V6;
    f2(FRONT, P4) = V5;
    //side 2
    f2(RIGHT, P1) = V2;
    f2(RIGHT, P2) = V3;
    f2(RIGHT, P3) = V7;
    f2(RIGHT, P4) = V6;
    //side 3
    f2(BACK, P1) = V3;
    f2(BACK, P2) = V4;
    f2(BACK, P3) = V8;
    f2(BACK, P4) = V7;
    //side 4
    f2(LEFT, P1) = V4;
    f2(LEFT, P2) = V1;
    f2(LEFT, P3) = V5;
    f2(LEFT, P4) = V8;
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

QJsonObject Cube::toJson() const {
    auto json = Polygon::toJson();
    json.insert("type", "CUBE");
    return json;
}
