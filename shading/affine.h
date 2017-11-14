//
// Created by Max Heartfield on 14.11.17.
//

#ifndef PLANE3D_AFFINE_H_H
#define PLANE3D_AFFINE_H_H

#include <QtGlobal>
#include <QGenericMatrix>
#include <cmath>
#include "common.h"

namespace affine {
    Matrix inverse(Matrix m);

    Matrix scale(const Matrix &m, double sx, double sy, double sz);

    Matrix translate(const Matrix &m, double dx, double dy, double dz);

    Matrix rotateX(const Matrix &m, double phi);

    Matrix rotateY(const Matrix &m, double phi);

    Matrix rotateZ(const Matrix &m, double phi);

    Matrix otrProject(const Matrix &m);

    Matrix perProject(const Matrix &m, double depth);
//double get_sign(QGenericMatrix<1, 3, qreal> v, QGenericMatrix<3, 1, qreal> m);
}


#endif //PLANE3D_AFFINE_H_H
