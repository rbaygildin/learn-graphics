//
// Created by Max Heartfield on 15.11.17.
//

#ifndef PLANE3D_SPIRAL_H
#define PLANE3D_SPIRAL_H

#include <QJsonObject>
#include "../../affine.h"

#include "nonconvex_figure.h"

class Spiral : public NonConvexFigure{

public:
    explicit Spiral(double R = 60, double r = 40, QObject *parent = nullptr);
    Matrix* vertices() override;
    QJsonObject toJson() const override;

private:
    std::vector<double> getCoords(ULONG row, ULONG c) override;

private:
    double R, r;

};


#endif //PLANE3D_SPIRAL_H
