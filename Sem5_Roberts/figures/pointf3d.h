//
// Created by Max Heartfield on 09.11.17.
//

#ifndef SEM5_ROBERTS_POINTF3D_H
#define SEM5_ROBERTS_POINTF3D_H

struct PointF3d{
    double x;
    double y;
    double z;
    PointF3d(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

#endif //SEM5_ROBERTS_POINTF3D_H
