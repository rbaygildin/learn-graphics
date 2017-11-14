#include "octahedron.h"

Octahedron::Octahedron(double edge, QVector3D center) : Polygon(edge, center){

}


unsigned int Octahedron::getV() const {
    return 6;
}

unsigned int Octahedron::getE() const {
    return 12;
}

unsigned int Octahedron::getF() const {
    return 8;
}

unsigned int Octahedron::getP() const {
    return 3;
}

Matrix Octahedron::vertices() const {
    Matrix v(getV(), 3);
    //v 1
    v(V1, X) = -this->edge / 2.0;
    v(V1, Y) = 0;
    v(V1, Z) = -this->edge / 2.0;
    //v 2
    v(V2, X) = this->edge / 2.0;
    v(V2, Y) = 0;
    v(V2, Z) = -this->edge / 2.0;
    //v 3
    v(V3, X) = this->edge / 2.0;
    v(V3, Y) = 0;
    v(V3, Z) = this->edge / 2.0;
    //v 4
    v(V4, X) = -this->edge / 2.0;
    v(V4, Y) = 0;
    v(V4, Z) = this->edge / 2.0;
    //v 5
    v(V5, X) = 0;
    v(V5, Y) = this->edge * sqrt(2) / 2;
    v(V5, Z) = 0;
    //v 6
    v(V6, X) = 0;
    v(V6, Y) = -this->edge * sqrt(2) / 2;
    v(V6, Z) = 0;

    return v;
}

IntMatrix Octahedron::faces() const {
    IntMatrix f(getF(), getP());
    //front top
    f(FRONT_TOP, P1) = V1;
    f(FRONT_TOP, P2) = V2;
    f(FRONT_TOP, P3) = V5;
    //right top
    f(RIGHT_TOP, P1) = V2;
    f(RIGHT_TOP, P2) = V3;
    f(RIGHT_TOP, P3) = V5;
    //back top
    f(BACK_TOP, P1) = V3;
    f(BACK_TOP, P2) = V4;
    f(BACK_TOP, P3) = V5;
    //left top
    f(LEFT_TOP, P1) = V4;
    f(LEFT_TOP, P2) = V1;
    f(LEFT_TOP, P3) = V5;
    //front bottom
    f(FRONT_BOTTOM, P1) = V1;
    f(FRONT_BOTTOM, P2) = V2;
    f(FRONT_BOTTOM, P3) = V6;
    //right bottom
    f(RIGHT_BOTTOM, P1) = V2;
    f(RIGHT_BOTTOM, P2) = V3;
    f(RIGHT_BOTTOM, P3) = V6;
    //back bottom
    f(BACK_BOTTOM, P1) = V3;
    f(BACK_BOTTOM, P2) = V4;
    f(BACK_BOTTOM, P3) = V6;
    //left bottom
    f(LEFT_BOTTOM, P1) = V4;
    f(LEFT_BOTTOM, P2) = V1;
    f(LEFT_BOTTOM, P3) = V6;
    return f;
}

QJsonObject Octahedron::toJson() const {
    auto json = Polygon::toJson();
    json.insert("type", "OCTAHEDRON");
    return json;
}
