#ifndef ICOSAHEDRON_H
#define ICOSAHEDRON_H


#include "polygon.h"

class Icosahedron : public Polygon {
public functions:

    Icosahedron(double edge = 50, QVector3D center = QVector3D(0, 0, 0));

    virtual QJsonObject toJson() const;

    unsigned int getV() const override;

    unsigned int getE() const override;

    unsigned int getF() const override;

    unsigned int getP() const override;

    Matrix vertices() const override;

    IntMatrix faces() const override;

private fields:
    static const int TOP = 0;
    static const int TOP_V1 = 1;
    static const int TOP_V2 = 2;
    static const int TOP_V3 = 3;
    static const int TOP_V4 = 4;
    static const int TOP_V5 = 5;
    static const int BOTTOM_V1 = 6;
    static const int BOTTOM_V2 = 7;
    static const int BOTTOM_V3 = 8;
    static const int BOTTOM_V4 = 9;
    static const int BOTTOM_V5 = 10;
    static const int BOTTOM = 11;
};

#endif // ICOSAHEDRON_H