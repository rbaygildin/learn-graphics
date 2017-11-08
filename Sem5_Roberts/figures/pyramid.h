//
// Created by Roman Yarnykh on 31.10.17.
//

#ifndef SEM5_ROBERTS_PYRAMID_H
#define SEM5_ROBERTS_PYRAMID_H


#include "figure.h"

#define PYRAMID_V1 0
#define PYRAMID_V2 1
#define PYRAMID_V3 2
#define PYRAMID_V4 3

#define PYRAMID_V 4
#define PYRAMID_E 6
#define PYRAMID_F 4
#define PYRAMID_P 3

#define PYRAMID_SIDE_RIGHT 1
#define PYRAMID_SIDE_LEFT 0
#define PYRAMID_SIDE_BACK 2
#define PYRAMID_BOTTOM 3

#define PYRAMID_P1 0
#define PYRAMID_P2 1
#define PYRAMID_P3 2
#define PYRAMID_P4 3

class Pyramid : public Figure<PYRAMID_V, PYRAMID_E, PYRAMID_F, PYRAMID_P>{
public:
    Pyramid(double edge, QGraphicsScene *scene);

    QJsonObject toJson() override;

protected:
    QGenericMatrix<PYRAMID_V, 3, qreal> vertex() override;
    QGenericMatrix<PYRAMID_F, PYRAMID_P, qreal> faces() override;
    QRectF bound() override;
};


#endif //SEM5_ROBERTS_PYRAMID_H
