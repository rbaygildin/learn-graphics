//
// Created by Roman Yarnykh on 01.11.17.
//

#ifndef SEM5_ROBERTS_OCTAHEDRON_H
#define SEM5_ROBERTS_OCTAHEDRON_H

#include "figure.h"

#define OCT_V 6
#define OCT_E 12
#define OCT_F 8
#define OCT_P 3

#define OCT_V1 0
#define OCT_V2 1
#define OCT_V3 2
#define OCT_V4 3
#define OCT_V5 4
#define OCT_V6 5

#define OCT_FRONT_TOP 0
#define OCT_SIDE_RIGHT_TOP 1
#define OCT_SIDE_BACK_TOP 2
#define OCT_SIDE_LEFT_TOP 3
#define OCT_FRONT_BOTTOM 4
#define OCT_SIDE_RIGHT_BOTTOM 5
#define OCT_SIDE_BACK_BOTTOM 6
#define OCT_SIDE_LEFT_BOTTOM 7

#define OCT_P1 0
#define OCT_P2 1
#define OCT_P3 2



class Octahedron : public Figure<OCT_V, OCT_E, OCT_F, OCT_P>{
public:
    Octahedron(double edge, QGraphicsScene *scene);

    QJsonObject toJson() override;

protected:
    QGenericMatrix<OCT_V, 3, qreal> vertex() override;
    QGenericMatrix<OCT_F, OCT_P, int> faces() override;
    QRectF bound() override;
};


#endif //SEM5_ROBERTS_OCTAHEDRON_H
