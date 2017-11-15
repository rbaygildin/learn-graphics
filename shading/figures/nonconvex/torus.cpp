#include <QJsonObject>
#include "torus.h"
#include "../../affine.h"

QJsonObject Torus::toJson() const {
    QJsonObject json;
    json.insert("type", "TORUS");
    json.insert("R", R);
    json.insert("r", r);
    return json;
}

Torus::Torus(double R, double r, QObject *parent) : NonConvexFigure(parent), R(R), r(r) {

}

std::vector<double> Torus::getCoords(ULONG row, ULONG column) {
    double phi = 2 * M_PI / hCount * row - M_PI;
    double xi = 2 * M_PI / vCount * column;
    std::vector<double> res(3);
    res[0] = (R + r * cos(phi)) * cos(xi);
    res[1] = (R + r * cos(phi)) * sin(xi);
    res[2] = r * sin(phi);
    return res;
}
