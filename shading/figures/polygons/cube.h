#ifndef CUBE_H
#define CUBE_H


#include "polygon.h"

class Cube : public Polygon {

public functions:

    explicit Cube(double edge = 50, QVector3D center = QVector3D(0, 0, 0));
    virtual QJsonObject toJson() const;

private functions:

    Matrix vertices() const override;

    IntMatrix faces() const override;

    unsigned int getV() const override;

    unsigned int getE() const override;

    unsigned int getF() const override;

    unsigned int getP() const override;

private fields:
    static constexpr ULONG FRONT = 0;
    static constexpr ULONG RIGHT = 1;
    static constexpr ULONG BACK = 2;
    static constexpr ULONG LEFT = 3;
    static constexpr ULONG BOTTOM = 4;
    static constexpr ULONG TOP = 5;
};

#endif // CUBE_H