//
// Created by Roman Yarnykh on 01.11.17.
//

#ifndef SEM5_ROBERTS_ICOSAHEDRON_H
#define SEM5_ROBERTS_ICOSAHEDRON_H


#include "figure.h"

#define ICOS_TOP 0
#define ICOS_TOP_V1 1
#define ICOS_TOP_V2 2
#define ICOS_TOP_V3 3
#define ICOS_TOP_V4 4
#define ICOS_TOP_V5 5
#define ICOS_BOTTOM_V1 6
#define ICOS_BOTTOM_V2 7
#define ICOS_BOTTOM_V3 8
#define ICOS_BOTTOM_V4 9
#define ICOS_BOTTOM_V5 10
#define ICOS_BOTTOM 11

class Icosahedron : public Figure{
public:
    Icosahedron(double edge, QGraphicsScene *scene);

protected:
    arma::mat vertex() override;
    arma::mat faces() override;
    int getV() override;
    int getE() override;
    int getF() override;
    int getP() override;
};


#endif //SEM5_ROBERTS_ICOSAHEDRON_H
