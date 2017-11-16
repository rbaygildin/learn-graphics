//
// Created by Max Heartfield on 15.11.17.
//

#include "spiral.h"

Spiral::Spiral(double R, double r, QObject *parent) : NonConvexFigure(parent), R(R), r(r) {

}

QJsonObject Spiral::toJson() const {
    QJsonObject json;
    json.insert("type", "SPIRAL");
    json.insert("R", R);
    json.insert("r", r);
    return json;
}

std::vector<double> Spiral::getCoords(ULONG row, ULONG c) {
    return std::vector<double>();
}

Matrix *Spiral::vertices() {
    if (vs != nullptr)
        return vs;
    vs = new Matrix(vCount * hCount, 3);
    double k = 1.0;
    double p = 10.0;
    R = 100;
    r = 20;
    for (ULONG column = 0; column < hCount; column++) {
        for (ULONG row = 0; row < vCount; row++) {
            double teta = 2 * M_PI / vCount * (column + 1);
            double v = 10 * M_PI / hCount * (row + 1);
            double x = (R + v * 5 + r * cos(teta)) * cos(v);
            double y = (R + v * 5 + r * cos(teta)) * sin(v);
            double z = r * sin(teta) + v * 10;
            vs->operator()(row * hCount + column, 0) = x;
            vs->operator()(row * hCount + column, 1) = y;
            vs->operator()(row * hCount + column, 2) = z;
        }
//        p += 0.5;
//        k += 0.3;
    }
    return vs;
}
