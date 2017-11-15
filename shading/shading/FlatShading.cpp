//
// Created by Max Heartfield on 14.11.17.
//

#include "FlatShading.h"

FlatShading::FlatShading(double ia, double id, double ka, QVector3D lightPoint) {

}

QColor FlatShading::getColor(QColor color, QVector3D normal) {
    double ambient = ia * 0.5;
    double diffuse = id * 0.5;
    double res = ambient + diffuse;
    res = res > 1.0 ? 1.0 : res;
    return QColor::fromRgbF(color.red() * res, color.green() * res, color.blue() * res, 1.0);
}
