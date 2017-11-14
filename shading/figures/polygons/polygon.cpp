#include "polygon.h"

Polygon::Polygon(double edge, const QVector3D &center) : edge(edge), center(center) {

}

QRectF Polygon::boundingRect() const {
    Matrix v = const_cast<Polygon*>(this)->applyTransformations();
    double xMin = numeric_limits<double>::max();
    double xMax = numeric_limits<double>::min();
    double yMin = numeric_limits<double>::max();
    double yMax = numeric_limits<double>::min();
    for (ULONG i = 0; i < getV(); i++) {
        double x = v(i, 0);
        double y = v(i, 1);
        if (x < xMin)
            xMin = x;
        if (x > xMax)
            xMax = x;
        if (y < yMin)
            yMin = y;
        if (y > yMax)
            yMax = y;
    }
    return QRectF(QPointF(xMin, -yMin), QPointF(xMax, -yMax));
}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    IntMatrix f = faces();
    Matrix v = applyTransformations();
    painter->setBrush(Qt::transparent);
    painter->setPen(Qt::black);
    QRectF b = boundingRect();
//    painter->scale(1, -1);
    for (int i = 0; i < getF(); i++) {
        QPolygonF face;
        for (int j = 0; j < getP(); j++) {
            face << QPointF(
                    v(f(i, j), 0),
                    -v(f(i, j), 1)
            );
        }
        painter->drawPolygon(face);
    }
    painter->setPen(Qt::red);
    painter->setBrush(Qt::transparent);
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Polygon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit signal1();
    QGraphicsItem::mousePressEvent(event);
}

void Polygon::setEdge(double edge) {
    this->edge = edge;
}

void Polygon::setCenter(QVector3D center) {
    this->center = center;
}

QJsonObject Polygon::toJson() const {
    QJsonObject json;
    json.insert("edge", edge);
    QJsonArray array;
    for (double transformation : transformations) {
        array.push_back(transformation);
    }
    json.insert("transformations", array);
    return json;
}

Matrix Polygon::applyTransformations() {
    Matrix v = vertices();
    v = affine::scale(v, transformations[ScaleX], transformations[ScaleY], transformations[ScaleZ]);
    v = affine::translate(v, transformations[TranslateX], transformations[TranslateY], transformations[TranslateZ]);
    v = affine::rotateX(v, transformations[RotateX]);
    v = affine::rotateX(v, transformations[RotateY]);
    v = affine::rotateX(v, transformations[RotateZ]);
    return v;
}
