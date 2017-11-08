//
// Created by Roman Yarnykh on 31.10.17.
//

#include "affine.h"

QGenericMatrix<3, 3, qreal> inverseMatrix(QGenericMatrix<3, 3, qreal> m) {
    // computes the inverseMatrix of a matrix m
    double det = m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) -
                 m(1, 0) * (m(0, 1) * m(2, 2) - m(2, 1) * m(0, 2)) +
                 m(2, 0) * (m(0, 1) * m(1, 2) - m(1, 1) * m(0, 2));

    double invDet = 1 / det;

    QGenericMatrix<3, 3, qreal> result; // inverseMatrix of matrix m
    result(0, 0) = (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) * invDet;
    result(1, 0) = (m(2, 0) * m(1, 2) - m(1, 0) * m(2, 2)) * invDet;
    result(2, 0) = (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * invDet;
    result(0, 1) = (m(2, 1) * m(0, 2) - m(0, 1) * m(2, 2)) * invDet;
    result(1, 1) = (m(0, 0) * m(2, 2) - m(2, 0) * m(0, 2)) * invDet;
    result(2, 1) = (m(0, 1) * m(2, 0) - m(0, 0) * m(2, 1)) * invDet;
    result(0, 2) = (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * invDet;
    result(1, 2) = (m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2)) * invDet;
    result(2, 2) = (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) * invDet;
    return result;
}

QGenericMatrix<3, 3, qreal> scaleMatrix(double a, double b, double c){
    QGenericMatrix<3, 3, qreal> projMatrix;
    //first row x
    projMatrix(0, 0) = a;
    projMatrix(1, 0) = 0;
    projMatrix(2, 0) = 0;
    //second row y
    projMatrix(0, 1) = 0;
    projMatrix(1, 1) = b;
    projMatrix(2, 1) = 0;
    //third row z - drop
    projMatrix(0, 2) = 0;
    projMatrix(1, 2) = 0;
    projMatrix(2, 2) = c;
    return projMatrix;
}

QGenericMatrix<4, 4, qreal> translationMatrix(double dx, double dy, double dz){
    QGenericMatrix<4, 4, qreal> projMatrix;
    //first row x
    projMatrix(0, 0) = 1;
    projMatrix(1, 0) = 0;
    projMatrix(2, 0) = 0;
    projMatrix(3, 0) = dx;
    //second row y
    projMatrix(0, 1) = 0;
    projMatrix(1, 1) = 1;
    projMatrix(2, 1) = 0;
    projMatrix(3, 1) = dy;
    //third row z - drop
    projMatrix(0, 2) = 0;
    projMatrix(1, 2) = 0;
    projMatrix(2, 2) = 1;
    projMatrix(3, 2) = dz;
    //
    projMatrix(0, 3) = 0;
    projMatrix(1, 3) = 0;
    projMatrix(2, 3) = 0;
    projMatrix(3, 3) = 1;
    return projMatrix;
}

QGenericMatrix<3, 3, qreal> rotationXMatrix(double phi){
    QGenericMatrix<3, 3, qreal> projMatrix;
    //first row x
    projMatrix(0, 0) = 1;
    projMatrix(1, 0) = 0;
    projMatrix(2, 0) = 0;
    //second row y
    projMatrix(0, 1) = 0;
    projMatrix(1, 1) = cos(phi);
    projMatrix(2, 1) = -sin(phi);
    //third row z - drop
    projMatrix(0, 2) = 0;
    projMatrix(1, 2) = sin(phi);
    projMatrix(2, 2) = cos(phi);
    return projMatrix;
}

QGenericMatrix<3, 3, qreal> rotationYMatrix(double phi){
    QGenericMatrix<3, 3, qreal> projMatrix;
    //first row x
    projMatrix(0, 0) = cos(phi);
    projMatrix(1, 0) = 0;
    projMatrix(2, 0) = sin(phi);
    //second row y
    projMatrix(0, 1) = 0;
    projMatrix(1, 1) = 1;
    projMatrix(2, 1) = 0;
    //third row z - drop
    projMatrix(0, 2) = -sin(phi);
    projMatrix(1, 2) = 0;
    projMatrix(2, 2) = cos(phi);
    return projMatrix;
}

QGenericMatrix<3, 3, qreal> rotationZMatrix(double phi){
    QGenericMatrix<3, 3, qreal> projMatrix;
    //first row x
    projMatrix(0, 0) = cos(phi);
    projMatrix(1, 0) = -sin(phi);
    projMatrix(2, 0) = 0;
    //second row y
    projMatrix(0, 1) = sin(phi);
    projMatrix(1, 1) = cos(phi);
    projMatrix(2, 1) = 0;
    //third row z - drop
    projMatrix(0, 2) = 0;
    projMatrix(1, 2) = 0;
    projMatrix(2, 2) = 1;
    return projMatrix;
}

QGenericMatrix<3, 3, qreal> otrProjectionMatrix(){
    QGenericMatrix<3, 3, qreal> projMatrix;
    //first row x
    projMatrix(0, 0) = 1;
    projMatrix(1, 0) = 0;
    projMatrix(2, 0) = 0;
    //second row y
    projMatrix(0, 1) = 0;
    projMatrix(1, 1) = 1;
    projMatrix(2, 1) = 0;
    //third row z - drop
    projMatrix(0, 2) = 0;
    projMatrix(1, 2) = 0;
    projMatrix(2, 2) = 0;
    return projMatrix;
}

QGenericMatrix<4, 4, qreal> perProjectionMatrix(double fov, double far, double near){
    QGenericMatrix<4, 4, qreal> pm;
    double S = 1 / tan(fov * 3.1459 / 360.0);
    double fn = far - near;
    //first row
    pm(0, 0) = S;
    pm(1, 0) = 0;
    pm(2, 0) = 0;
    pm(3, 0) = 0;
    //second row
    pm(0, 1) = 0;
    pm(1, 1) = S;
    pm(2, 1) = 0;
    pm(3, 1) = 0;
    //third row
    pm(0, 2) = 0;
    pm(1, 2) = 0;
    pm(2, 2) = - far / fn;
    pm(3, 2) = -1.0;
    //fourth row
    pm(0, 3) = 0;
    pm(1, 3) = 0;
    pm(2, 3) = - far * near / fn;
    pm(3, 3) = 0;
    return pm;
};

double get_sign(QGenericMatrix<1, 3, qreal> v, QGenericMatrix<3, 1, qreal> m){
    double s;
    s = v(0, 0) * m(0, 0) + v(1, 0) * m(0, 1) + v(2, 0) * m(0, 2);
    return s;
}