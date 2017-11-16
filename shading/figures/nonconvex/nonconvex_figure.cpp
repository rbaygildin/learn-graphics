//
// Created by Max Heartfield on 15.11.17.
//

#include "nonconvex_figure.h"

QRectF NonConvexFigure::boundingRect() const {
    double xMin = numeric_limits<double>::max();
    double xMax = numeric_limits<double>::min();
    double yMin = numeric_limits<double>::max();
    double yMax = numeric_limits<double>::min();
    Matrix v = const_cast<NonConvexFigure *>(this)->applyTr();
    for (ULONG column = 0; column < hCount; column++) {
        for (ULONG row = 0; row < vCount; row++) {
            double x = v.operator()(row * hCount + column, 0);
            double y = v.operator()(row * hCount + column, 1);
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

void NonConvexFigure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (mode == MESH)
        paintMesh(painter);
    else
        paintWithLighting(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

Matrix NonConvexFigure::applyTr() {
    Matrix v(*vertices());
    v = geom::scale(v, transformations[ScaleX], transformations[ScaleY], transformations[ScaleZ]);
    v = geom::translate(v, transformations[TranslateX], transformations[TranslateY], transformations[TranslateZ]);
    v = geom::rotateX(v, transformations[RotateX]);
    v = geom::rotateY(v, transformations[RotateY]);
    v = geom::rotateZ(v, transformations[RotateZ]);
    return v;
}

NonConvexFigure::NonConvexFigure(QObject *parent) : Figure(parent) {

}

NonConvexFigure::~NonConvexFigure() {
    delete vs;
}

Matrix *NonConvexFigure::vertices() {
    if (vs != nullptr)
        return vs;
    vs = new Matrix(vCount * hCount, 3);
    for (ULONG column = 0; column < hCount; column++) {
        for (ULONG row = 0; row < vCount; row++) {
            std::vector<double> coords = getCoords(row, column);
            vs->operator()(row * hCount + column, 0) = coords[0];
            vs->operator()(row * hCount + column, 1) = coords[1];
            vs->operator()(row * hCount + column, 2) = coords[2];
        }
    }
    return vs;
}

QColor NonConvexFigure::flatShading(QColor color, double ia, double id, double ka, QVector3D n, QVector3D l) {
    double cos_ = QVector3D::dotProduct(n, l) / (n.length() * l.length());
    double res = ia * 0.1 + id * ka * cos_;
    res = res > 1 ? 1 : (res < 0 ? 0 : res);
    return QColor::fromRgbF(color.redF() * res, color.greenF() * res, color.blueF() * res, 1.0);
}

QVector3D NonConvexFigure::normal(QVector3D a, QVector3D b) {
    return QVector3D::crossProduct(a.normalized(), b.normalized());
}

void NonConvexFigure::paintMesh(QPainter *painter) {
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
            QVector3D a(
                    face.boundingRect().bottomRight() - face.boundingRect().bottomLeft()
            );
            QVector3D b(
                    face.boundingRect().topRight() - face.boundingRect().bottomRight()
            );
//            QVector3D l(1000, 100, 100);
//            painter->setBrush(QBrush(flatShading(Qt::red, 1, 10, 0.6, normal(b, a), l)));
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
    painter->setPen(Qt::red);
    painter->setBrush(Qt::transparent);
    painter->drawRect(boundingRect());
}

void NonConvexFigure::paintWithLighting(QPainter *painter) {
    Matrix v = applyTr();
    painter->setPen(Qt::transparent);
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
            QVector3D a(
                    face.boundingRect().bottomRight() - face.boundingRect().bottomLeft()
            );
            QVector3D b(
                    face.boundingRect().topRight() - face.boundingRect().bottomRight()
            );
            painter->setBrush(QBrush(flatShading(a, b)));
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
        QVector3D a(
                face.boundingRect().bottomRight() - face.boundingRect().bottomLeft()
        );
        QVector3D b(
                face.boundingRect().topRight() - face.boundingRect().bottomRight()
        );
        painter->setBrush(QBrush(flatShading(a, b)));
        painter->drawPolygon(face);
    }
    painter->setPen(Qt::red);
    painter->setBrush(Qt::transparent);
    painter->drawRect(boundingRect());
}

QColor NonConvexFigure::flatShading(QVector3D a, QVector3D b) {
    QVector3D normal;
    normal.setX(0.0);
    normal.setY(0.0);
    normal.setZ(0.0);
    a.normalize();
    b.normalize();
    QVector3D n = QVector3D::crossProduct(a, b);
    QVector3D lighter;
    lighter.setX(lamp.x());
    lighter.setY(lamp.y());
    lighter.setZ(lamp.z());
    n.normalize();
    lighter.normalize();
    double cos_ = QVector3D::dotProduct(n, lighter);
    double ambient = ia * 0.5;
    double diffuse = id * 0.5 * max(cos_, 0.0);
    double res = (ambient + diffuse) * 0.1;
    return QColor::fromRgbF(min(1.0, color.redF() * res),
                            min(1.0, color.greenF() * res),
                            min(1.0, color.blueF() * res), 1.0);
}
