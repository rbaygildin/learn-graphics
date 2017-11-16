//
// Created by Max Heartfield on 15.11.17.
//

#include "klein_bottle.h"

#include <QJsonObject>
#include "../../affine.h"

QRectF KleinBottle::boundingRect() const {
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

void KleinBottle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
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

Matrix KleinBottle::applyTr() {
    Matrix v(*vs);
    v = geom::scale(v, transformations[ScaleX], transformations[ScaleY], transformations[ScaleZ]);
    v = geom::translate(v, transformations[TranslateX], transformations[TranslateY], transformations[TranslateZ]);
    v = geom::rotateX(v, transformations[RotateX]);
    v = geom::rotateY(v, transformations[RotateY]);
    v = geom::rotateZ(v, transformations[RotateZ]);
    return v;
}

QJsonObject KleinBottle::toJson() const {
    QJsonObject json;
    json.insert("type", "TORUS");
    json.insert("R", R);
    return json;
}

KleinBottle::KleinBottle(double R, QObject *parent) : Figure(parent), R(R){
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

KleinBottle::~KleinBottle() {
    delete vs;
}

std::vector<double> KleinBottle::getCoords(ULONG row, ULONG column) {
    double teta = 2 * M_PI / hCount * row;
    double v = 2 * M_PI / vCount * column;
    std::vector<double> res(3);
    res[0] = (R + cos(teta / 2.0) * sin(v) - sin(teta / 2.0) * sin(2 * v)) * cos(teta);
    res[1] = (R + cos(teta / 2.0) * sin(v) - sin(teta / 2.0) * sin(2 * v)) * sin(teta);
    res[2] = sin(teta / 2) * sin(v) + cos(teta / 2) * sin(2 * v);
    return res;
}

void KleinBottle::paintMesh(QPainter *painter) {

}

void KleinBottle::paintWithLighting(QPainter *painter) {

}
