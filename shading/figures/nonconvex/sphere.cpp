//
// Created by Max Heartfield on 15.11.17.
//

#include "sphere.h"

#include <QJsonObject>
#include "../../affine.h"

QJsonObject Sphere::toJson() const {
    QJsonObject json;
    json.insert("type", "SPHERE");
    json.insert("R", R);
    return json;
}

Sphere::Sphere(double R, QObject *parent) : NonConvexFigure(parent), R(R) {
}


std::vector<double> Sphere::getCoords(ULONG row, ULONG column) {
    double phi = 2 * M_PI / hCount * row;
    double teta = 2 * M_PI / vCount * column - M_PI;
    std::vector<double> res(3);
    res[0] = R * cos(phi) * sin(teta);
    res[1] = R * sin(phi) * sin(teta);
    res[2] = R * cos(teta);
    return res;
}
