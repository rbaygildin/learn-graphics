//
// Created by Roman Yarnykh on 31.10.17.
//

#ifndef SEM5_ROBERTS_AFFINE_H
#define SEM5_ROBERTS_AFFINE_H

#include <QtGlobal>
#include <QGenericMatrix>
#include <cmath>

QGenericMatrix<3, 3, qreal> inverseMatrix(QGenericMatrix<3, 3, qreal> m);
QGenericMatrix<3, 3, qreal> scaleMatrix(double a, double b, double c);
QGenericMatrix<4, 4, qreal> translationMatrix(double dx, double dy, double dz);
QGenericMatrix<3, 3, qreal> rotationXMatrix(double phi);
QGenericMatrix<3, 3, qreal> rotationYMatrix(double phi);
QGenericMatrix<3, 3, qreal> rotationZMatrix(double phi);
QGenericMatrix<3, 3, qreal> otrProjectionMatrix();
QGenericMatrix<4, 4, qreal> perProjectionMatrix(double fov, double far, double near);
double get_sign(QGenericMatrix<1, 3, qreal> v, QGenericMatrix<3, 1, qreal> m);


#endif //SEM5_ROBERTS_AFFINE_H
