//
// Created by Max Heartfield on 15.11.17.
//

#include "sphere.h"

#include <QJsonObject>
#include "../affine.h"

QRectF Sphere::boundingRect() const {
    double xMin = numeric_limits<double>::max();
    double xMax = numeric_limits<double>::min();
    double yMin = numeric_limits<double>::max();
    double yMax = numeric_limits<double>::min();
    for (ULONG column = 0; column < hCount; column++) {
        for (ULONG row = 0; row < vCount; row++) {
            double x = vs->operator()(row * hCount + column, 0);
            double y = vs->operator()(row * hCount + column, 1);
            if (x < xMin)
                xMin = x;
            if (x > xMax)
                xMax = x;
            if (y < yMin)
                yMin = y;
            if (y > yMax)
                yMax = y;
        }
    }
    return QRectF(QPointF(xMin, -yMin), QPointF(xMax, -yMax));
}

void Sphere::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Matrix v = applyTr();
    painter->setPen(Qt::black);
    for (int col = 1; col < hCount; col++) {
        for (int row = 1; row < vCount; row++) {
            QPolygonF face;
            face << QPointF(
                    v(row * hCount + col, 0),
                    -v(row * hCount + col, 1)
            ) << QPointF(
                    v((row - 1) * hCount + col, 0),
                    -v((row - 1) * hCount + col, 1)
            ) << QPointF(
                    v((row - 1) * hCount + col - 1, 0),
                    -v((row - 1) * hCount + col - 1, 1)
            ) << QPointF(
                    v(row * hCount + col - 1, 0),
                    -v(row * hCount + col - 1, 1)
            );
            painter->drawPolygon(face);
        }
    }
    //Замкнуть
    for (int row = 1; row < vCount; row++) {
        QPolygonF face;
        face << QPointF(
                v(row * hCount, 0),
                -v(row * hCount, 1)
        ) << QPointF(
                v((row - 1) * hCount, 0),
                -v((row - 1) * hCount, 1)
        ) << QPointF(
                v((row - 1) * hCount + hCount - 1, 0),
                -v((row - 1) * hCount + hCount - 1, 1)
        ) << QPointF(
                v(row * hCount + hCount - 1, 0),
                -v(row * hCount + hCount - 1, 1)
        );
        painter->drawPolygon(face);
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

Matrix Sphere::applyTr() {
    Matrix v(*vs);
    v = geom::scale(v, transformations[ScaleX], transformations[ScaleY], transformations[ScaleZ]);
    v = geom::translate(v, transformations[TranslateX], transformations[TranslateY], transformations[TranslateZ]);
    v = geom::rotateX(v, transformations[RotateX]);
    v = geom::rotateY(v, transformations[RotateY]);
    v = geom::rotateZ(v, transformations[RotateZ]);
    return v;
}

QJsonObject Sphere::toJson() const {
    QJsonObject json;
    json.insert("type", "TORUS");
    json.insert("R", R);
    return json;
}

Sphere::Sphere(double R, QObject *parent) : Figure(parent), R(R){
    vs = new Matrix(vCount * hCount, 3);
    for (ULONG column = 0; column < hCount; column++) {
        for (ULONG row = 0; row < vCount; row++) {
            std::vector<double> coords = getCoords(row, column);
            vs->operator()(row * hCount + column, 0) = coords[0];
            vs->operator()(row * hCount + column, 1) = coords[1];
            vs->operator()(row * hCount + column, 2) = coords[2];
        }
    }
}

Sphere::~Sphere() {
    delete vs;
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
