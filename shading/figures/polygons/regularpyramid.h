#ifndef REGULARPYRAMID_H
#define REGULARPYRAMID_H


#include "polygon.h"

class RegularPyramid : public Polygon {
public FUNCTIONS:

    RegularPyramid();

    unsigned int getV() const override;

    unsigned int getE() const override;

    unsigned int getF() const override;

    unsigned int getP() const override;

    Matrix verteces() const override;

    IntMatrix faces() const override;

private FIELDS:
    static constexpr ULONG LEFT = 0;
    static constexpr ULONG RIGHT = 1;
    static constexpr ULONG BACK = 2;
    static constexpr ULONG BOTTOM = 3;
};

#endif // REGULARPYRAMID_H