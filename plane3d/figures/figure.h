//
// Created by Roman Yarnykh on 31.10.17.
//

#ifndef SEM5_ROBERTS_FIGURE_H
#define SEM5_ROBERTS_FIGURE_H


#include <QGraphicsScene>
#include <QGenericMatrix>
#include <cmath>
#include <vector>
#include <armadillo>
#include "../affine/affine.h"

using namespace std;

#define X 0
#define Y 1
#define Z 2

#define PI 3.1459

class Figure {
public:
    Figure(double edge, QGraphicsScene *scene);

public:
    Figure *rotate(double a, double b, double c);

    Figure *scale(double a, double b, double c);

    Figure *translate(double dx, double dy, double dz);

    Figure *parProject();

    Figure *perspectiveProject(double depth);

//    Figure *removeHiddenLines(bool flag);

    void paint();

protected:
    virtual int getV() = 0;
    virtual int getE() = 0;
    virtual int getF() = 0;
    virtual int getP() = 0;
    virtual arma::mat vertex() = 0;
    virtual arma::mat faces() = 0;

protected:
    double rx2sx(double x);
    double ry2sy(double y);

protected:
    bool isRemoveLines = false;
    QGraphicsScene *scene;
    arma::mat v;
    arma::mat pV;
    arma::mat f;
    vector<bool> hidden;
    double edge;
};

#endif //SEM5_ROBERTS_FIGURE_H
