#ifndef REGULARPYRAMID_H
#define REGULARPYRAMID_H


#include "polygon.h"

class RegularPyramid : public Polygon {
public functions:

    explicit RegularPyramid(double edge = 50, QVector3D center = QVector3D(0, 0, 0));

    virtual QJsonObject toJson() const;

    unsigned int getV() const override;

    unsigned int getE() const override;

    unsigned int getF() const override;

    unsigned int getP() const override;

    Matrix vertices() const override;

    IntMatrix faces() const override;

private fields:
    static constexpr ULONG LEFT = 0;
    static constexpr ULONG RIGHT = 1;
    static constexpr ULONG BACK = 2;
    static constexpr ULONG BOTTOM = 3;
};

#endif // REGULARPYRAMID_H