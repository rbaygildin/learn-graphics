#ifndef PYRAMID_H
#define PYRAMID_H


#include "polygon.h"
#include "../../point3d.h"

class Pyramid : public Polygon
{
public:
    Pyramid(Point3D v1, Point3D v2, Point3D v3, Point3D v4);

    unsigned int getV() const override;

    unsigned int getE() const override;

    unsigned int getF() const override;

    unsigned int getP() const override;

    Matrix vertices() const override;

    IntMatrix faces() const override;

    QJsonObject toJson() const override;

private:
    Matrix vertices_;
    Matrix faces_;
    static const ULONG LEFT = 0;
    static const ULONG RIGHT = 1;
    static const ULONG BACK = 2;
    static const ULONG BOTTOM = 3;

};

#endif // PYRAMID_H