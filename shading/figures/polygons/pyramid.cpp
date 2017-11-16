#include "pyramid.h"
#include "../../point3d.h"

Pyramid::Pyramid(Point3D v1, Point3D v2, Point3D v3, Point3D v4) {
    vertices_ = Matrix(getV(), 3);
    faces_ = IntMatrix(getF(), getP());
    //vertices
    //v 1
    vertices_(V1, X) = v1.x;
    vertices_(V1, Y) = v1.y;
    vertices_(V1, Z) = v1.z;
    //v 2
    vertices_(V2, X) = v2.x;
    vertices_(V2, Y) = v2.y;
    vertices_(V2, Z) = v2.z;
    //v 3
    vertices_(V3, X) = v3.x;
    vertices_(V3, Y) = v3.y;
    vertices_(V3, Z) = v3.z;
    //v 4
    vertices_(V4, X) = v4.x;
    vertices_(V4, Y) = v4.y;
    vertices_(V4, Z) = v4.z;
    //side 1
    faces_(LEFT, P1) = V1;
    faces_(LEFT, P2) = V2;
    faces_(LEFT, P3) = V4;
    //side 2
    faces_(RIGHT, P1) = V2;
    faces_(RIGHT, P2) = V3;
    faces_(RIGHT, P3) = V4;
    //side 3
    faces_(BACK, P1) = V3;
    faces_(BACK, P2) = V1;
    faces_(BACK, P3) = V4;
    //bottom
    faces_(BOTTOM, P1) = V1;
    faces_(BOTTOM, P2) = V2;
    faces_(BOTTOM, P3) = V3;
}

unsigned int Pyramid::getV() const {
    return 4;
}

unsigned int Pyramid::getE() const {
    return 6;
}

unsigned int Pyramid::getF() const {
    return 4;
}

unsigned int Pyramid::getP() const {
    return 3;
}

Matrix Pyramid::vertices() const {
    return vertices_;
}

IntMatrix Pyramid::faces() const {
    return faces_;
}

QJsonObject Pyramid::toJson() const {
    QJsonObject json = Polygon::toJson();
    json["type"] = "PYRAMID";
    QJsonArray array;
    QJsonArray vertexArray;
    for (ULONG i = 0; i < getV(); i++) {
        for (ULONG j = 0; j < 3; j++) {
            vertexArray.push_back(vertices_(i, j));
        }
    }
    json.insert("vertex", vertexArray);
    return json;
}
