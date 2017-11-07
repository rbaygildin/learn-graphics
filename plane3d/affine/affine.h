//
// Created by Max Heartfield on 07.11.17.
//

#ifndef PLANE3D_AFFINE_H
#define PLANE3D_AFFINE_H

#include <armadillo>

class Affine{
public:
    static arma::mat inverse(arma::mat matrix);
    static arma::mat scale(arma::mat matrix, double a, double b, double c);
    static arma::mat translate(arma::mat matrix, double dx, double dy, double dz);
    static arma::mat rotate(arma::mat matrix, double a, double b, double c);
    static arma::mat rotateX(arma::mat matrix, double phi);
    static arma::mat rotateY(arma::mat matrix, double phi);
    static arma::mat rotateZ(arma::mat matrix, double phi);
    static arma::mat parProject(arma::mat matrix);
    static arma::mat perProject(arma::mat matrix, double depth);
    static double getSign(arma::mat v, arma::mat m);
};

#endif //PLANE3D_AFFINE_H
