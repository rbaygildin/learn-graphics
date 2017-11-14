#ifndef CUBE_H
#define CUBE_H


#include "polygon.h"

class Cube : public Polygon {
public FUNCTIONS:

    explicit Cube(QObject *parent = 0);

    ~Cube() override = default;

private FUNCTIONS:

    Matrix verteces() const override;

    IntMatrix faces() const override;

    unsigned int getV() const override;

    unsigned int getE() const override;

    unsigned int getF() const override;

    unsigned int getP() const override;

private FIELDS:
    static constexpr ULONG FRONT = 0;
    static constexpr ULONG RIGHT = 1;
    static constexpr ULONG BACK = 2;
    static constexpr ULONG LEFT = 3;
    static constexpr ULONG BOTTOM = 4;
    static constexpr ULONG TOP = 5;
};

#endif // CUBE_H