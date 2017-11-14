#include "polygon.h"

Polygon::Polygon(double edge, const QVector3D &center) : edge(edge), center(center) {

}

QRectF Polygon::boundingRect() const {
    Matrix v = const_cast<Polygon *>(this)->applyTr();
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
    auto f = sortFaces();
    Matrix v = applyTr();
    painter->setPen(Qt::black);
    for (int i = 0; i < getF(); i++) {
        QPolygonF polygon;
        std::vector<int> face = f[i];
        for (int j = 0; j < getP(); j++) {
            polygon << QPointF(
                    v(face[j], 0),
                    -v(face[j], 1)
            );
        }
        painter->drawPolygon(polygon);
    }
//    painter->setPen(Qt::red);
//    painter->setBrush(Qt::transparent);
//    painter->drawRect(boundingRect());
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

Matrix Polygon::applyTr() {
    Matrix v = vertices();
    v = geom::scale(v, transformations[ScaleX], transformations[ScaleY], transformations[ScaleZ]);
    v = geom::translate(v, transformations[TranslateX], transformations[TranslateY], transformations[TranslateZ]);
    v = geom::rotateX(v, transformations[RotateX]);
    v = geom::rotateY(v, transformations[RotateY]);
    v = geom::rotateZ(v, transformations[RotateZ]);
    return geom::perProject(v, -200);
}

std::vector<std::vector<int>> Polygon::sortFaces() {
    IntMatrix f = faces();
    Matrix v = applyTr();
    std::vector<std::vector<int>> sortedFaces;
    for (ULONG i = 0; i < getF(); i++) {
        std::vector<int> p;
        for (ULONG j = 0; j < getP(); j++) {
            p.emplace_back(f(i, j));
        }
        sortedFaces.emplace_back(p);
    }
    std::sort(sortedFaces.begin(), sortedFaces.end(), [=](const std::vector<int> &a, const std::vector<int> &b) -> bool {
        double zA = 0.0;
        double zB = 0.0;
        for (ULONG i = 0; i < a.size(); i++) {
            zA += v(a[i], 2);
            zB += v(b[i], 2);
        }
        zA /= a.size();
        zB /= a.size();
        return zA < zB;
    });
    return sortedFaces;
}
