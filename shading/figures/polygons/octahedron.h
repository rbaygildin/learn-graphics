#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H


#include "polygon.h"

class Octahedron : public Polygon
{
public FUNCTIONS:
    Octahedron();

    unsigned int getV() const override;

    unsigned int getE() const override;

    unsigned int getF() const override;

    unsigned int getP() const override;

    Matrix verteces() const override;

    IntMatrix faces() const override;

private FIELDS:
    static const int FRONT_TOP = 0;
    static const int RIGHT_TOP = 1;
    static const int BACK_TOP = 2;
    static const int LEFT_TOP = 3;
    static const int FRONT_BOTTOM = 4;
    static const int RIGHT_BOTTOM = 5;
    static const int BACK_BOTTOM = 6;
    static const int LEFT_BOTTOM = 7;
};

#endif // OCTAHEDRON_H