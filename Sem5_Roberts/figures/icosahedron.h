//
// Created by Roman Yarnykh on 01.11.17.
//

#ifndef SEM5_ROBERTS_ICOSAHEDRON_H
#define SEM5_ROBERTS_ICOSAHEDRON_H


#include "figure.h"

#define ICOS_V 12
#define ICOS_E 30
#define ICOS_F 20
#define ICOS_P 3

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

#define ICOS_P1 0
#define ICOS_P2 1
#define ICOS_P3 2

class Icosahedron : public Figure<ICOS_V, ICOS_E, ICOS_F, ICOS_P>{
public:
    Icosahedron(double edge, QGraphicsScene *scene);

    QJsonObject toJson() override;

protected:
    QGenericMatrix<ICOS_V, 3, qreal> vertex() override;
    QGenericMatrix<ICOS_F, ICOS_P, qreal> faces() override;
    QRectF bound() override;
};


#endif //SEM5_ROBERTS_ICOSAHEDRON_H
