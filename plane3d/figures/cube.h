#ifndef CUBE_H
#define CUBE_H

#include <QGraphicsScene>
#include <QVector2D>
#include <cmath>
#include <algorithm>
#include <iterator>
#include "figure.h"

using namespace std;
const int V = 8;
const int E = 12;
const int F = 6;
const int P = 4;

const int XC = 0;
const int YC = 1;
const int ZC = 2;

const int V1 = 0;
const int V2 = 1;
const int V3 = 2;
const int V4 = 3;
const int V5 = 4;
const int V6 = 5;
const int V7 = 6;
const int V8 = 7;

const int SIDE_FRONT = 0;
const int SIDE_RIGHT = 1;
const int SIDE_BACK = 2;
const int SIDE_LEFT = 3;
const int TOP = 4;
const int BOTTOM = 5;

const int P1 = 0;
const int P2 = 1;
const int P3 = 2;
const int P4 = 3;

class Cube : public Figure
{
public:
    Cube(double edge, QGraphicsScene *scene);

protected:
    arma::mat vertex() override;
    arma::mat faces() override;
    int getV() override;
    int getE() override;
    int getF() override;
    int getP() override;
};

#endif // CUBE_H
