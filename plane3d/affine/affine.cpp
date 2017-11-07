//
// Created by Max Heartfield on 07.11.17.
//

#include "affine.h"

arma::mat Affine::inverse(arma::mat matrix) {
    return arma::mat();
}

arma::mat Affine::scale(arma::mat matrix, double a, double b, double c) {
    arma::mat sm;
    //first row x
    sm(0, 0) = a;
    sm(0, 1) = 0;
    sm(0, 2) = 0;
    //second row y
    sm(1, 0) = 0;
    sm(1, 1) = b;
    sm(1, 2) = 0;
    //third row z - drop
    sm(2, 0) = 0;
    sm(2, 1) = 0;
    sm(2, 2) = c;
    return matrix * sm;
}

arma::mat Affine::translate(arma::mat matrix, double dx, double dy, double dz) {
    arma::mat tm;
    //first row x
    tm(0, 0) = 1;
    tm(0, 1) = 0;
    tm(0, 2) = 0;
    tm(0, 3) = dx;
    //second row y
    tm(1, 0) = 0;
    tm(1, 1) = 1;
    tm(1, 2) = 0;
    tm(1, 3) = dy;
    //third row z - drop
    tm(2, 0) = 0;
    tm(2, 1) = 0;
    tm(2, 2) = 1;
    tm(2, 3) = dz;
    //
    tm(3, 0) = 0;
    tm(3, 1) = 0;
    tm(3, 2) = 0;
    tm(3, 3) = 1;
    return matrix * tm;
}

arma::mat Affine::rotateX(arma::mat matrix, double phi) {
    arma::mat rm;
    //first row x
    rm(0, 0) = 1;
    rm(0, 1) = 0;
    rm(0, 2) = 0;
    //second row y
    rm(1, 0) = 0;
    rm(1, 1) = cos(phi);
    rm(1, 2) = -sin(phi);
    //third row z - drop
    rm(2, 0) = 0;
    rm(2, 1) = sin(phi);
    rm(2, 2) = cos(phi);
    return matrix * rm;
}

arma::mat Affine::rotateY(arma::mat matrix, double phi) {
    arma::mat rm;
    //first row x
    rm(0, 0) = cos(phi);
    rm(0, 1) = 0;
    rm(0, 2) = sin(phi);
    //second row y
    rm(1, 0) = 0;
    rm(1, 1) = 1;
    rm(1, 2) = 0;
    //third row z - drop
    rm(2, 0) = -sin(phi);
    rm(2, 1) = 0;
    rm(2, 2) = cos(phi);
    return matrix * rm;
}

arma::mat Affine::rotateZ(arma::mat matrix, double phi) {
    arma::mat rm;
    //first row x
    rm(0, 0) = cos(phi);
    rm(0, 1) = -sin(phi);
    rm(0, 2) = 0;
    //second row y
    rm(1, 0) = sin(phi);
    rm(1, 1) = cos(phi);
    rm(1, 2) = 0;
    //third row z - drop
    rm(2, 0) = 0;
    rm(2, 1) = 0;
    rm(2, 2) = 1;
    return matrix * rm;
}

arma::mat Affine::parProject(arma::mat matrix) {
    arma::mat pm;
    //first row x
    pm(0, 0) = 1;
    pm(0, 1) = 0;
    pm(0, 2) = 0;
    //second row y
    pm(1, 0) = 0;
    pm(1, 1) = 1;
    pm(1, 2) = 0;
    //third row z - drop
    pm(2, 0) = 0;
    pm(2, 1) = 0;
    pm(2, 2) = 0;
    return matrix * pm;
}

arma::mat Affine::perProject(arma::mat matrix, double depth) {
    arma::mat pm;
    //first row
    pm(0, 0) = 1;
    pm(0, 1) = 0;
    pm(0, 2) = 0;
    pm(0, 3) = 0;
    //second row
    pm(1, 0) = 0;
    pm(1, 1) = 1;
    pm(1, 2) = 0;
    pm(1, 3) = 0;
    //third row
    pm(2, 0) = 0;
    pm(2, 1) = 0;
    pm(2, 2) = 0;
    pm(2, 3) = -1.0 / depth;
    //fourth row
    pm(3, 0) = 0;
    pm(3, 1) = 0;
    pm(3, 2) = 0;
    pm(3, 3) = 1;
    return matrix * pm;
}

double Affine::getSign(arma::mat v, arma::mat m) {
    return 0;
}

arma::mat Affine::rotate(arma::mat matrix, double a, double b, double c) {
    return rotateZ(rotateY(rotateX(matrix, a), b), c);
}
