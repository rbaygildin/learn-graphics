//
// Created by Max Heartfield on 14.11.17.
//

#ifndef PLANE3D_FLATSHADING_H
#define PLANE3D_FLATSHADING_H

#include <boost/numeric/ublas/vector.hpp>
#include <QColor>
#include <QVector3D>

using namespace boost::numeric::ublas;

class FlatShading {
public:
    FlatShading(double ia, double id, double ka, QVector3D lightPoint);
    QColor getColor(QColor color, QVector3D normal);

private:
    double ia, id, ka;
};


#endif //PLANE3D_FLATSHADING_H
