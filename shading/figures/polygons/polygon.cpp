#include "polygon.h"
#include <algorithm>

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
    if (mode == MESH)
        paintMesh(painter);
    else
        paintWithLighting(painter);
    if (isSelected()) {
        painter->setPen(Qt::red);
        painter->drawRect(boundingRect());
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
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
    return v;
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
    std::sort(sortedFaces.begin(), sortedFaces.end(),
              [=](const std::vector<int> &a, const std::vector<int> &b) -> bool {
                  double zA = 0.0;
                  double zB = 0.0;
                  for (ULONG i = 0; i < a.size(); i++) {
                      zA += v(a[i], 2);
                      zB += v(b[i], 2);
                  }
                  zA /= a.size();
                  zB /= a.size();
                  return zA > zB;
              });
    return sortedFaces;
}

QColor Polygon::flatShading(ULONG faceNumber, std::vector<int> face) {
    QVector3D normal;
    normal.setX(0.0);
    normal.setY(0.0);
    normal.setZ(0.0);
    auto v = applyTr();
    auto f = faces();
    QVector3D a;
    a.setX(v(face[P2], X) - v(face[P1], X));
    a.setY(v(face[P2], Y) - v(face[P1], Y));
    a.setZ(v(face[P2], Z) - v(face[P1], Z));
    QVector3D b;
    b.setX(v(face[P3], X) - v(face[P2], X));
    b.setY(v(face[P3], Y) - v(face[P2], Y));
    b.setZ(v(face[P3], Z) - v(face[P2], Z));
//    for (int i = 0, j = 1; i < getP(); i++, j++) {
//        if (j == getP()) j = 0;
//        normal.setX(normal.x() + (v(f(faceNumber, i), Z) - v(f(faceNumber, j), Z)) *
//                                 (v(f(faceNumber, i), Y) - v(f(faceNumber, i), Y))
//        );
//        normal.setY(normal.y() + (v(f(faceNumber, i), X) - v(f(faceNumber, j), X)) *
//                                 (v(f(faceNumber, i), Z) - v(f(faceNumber, j), Z))
//        );
//        normal.setZ(normal.z() + (v(f(faceNumber, i), Y) - v(f(faceNumber, j), Y)) *
//                                 (v(f(faceNumber, i), X) - v(f(faceNumber, j), X))
//        );
//    }
    a.normalize();
    b.normalize();
    QVector3D n = QVector3D::crossProduct(a, b);
    double xC = 0.0, yC = 0.0, zC = 0.0;
    for (ULONG i = 0; i < getP(); i++) {
        xC += v(face[i], X);
        yC += v(face[i], Y);
        zC += v(face[i], Z);
    }
    xC /= getP();
    yC /= getP();
    zC /= getP();
    QVector3D lighter;
    lighter.setX(lamp.x());
    lighter.setY(lamp.y());
    lighter.setZ(lamp.z());
    n.normalize();
    lighter.normalize();

    double cos_ = QVector3D::dotProduct(n, lighter);
    double ambient = ia * ka;
    double diffuse = id * kd * max(cos_, 0.0);
    double res = (ambient + diffuse) * 0.1;
    return QColor::fromRgbF(min(1.0, color.redF() * res),
                            min(1.0, color.greenF() * res),
                            min(1.0, color.blueF() * res), 1.0);
}

void Polygon::paintMesh(QPainter *painter) {
    auto f = faces();
    Matrix v = geom::perProject(applyTr(), 200);
    painter->setPen(Qt::black);
    for (ULONG i = 0; i < getF(); i++) {
        QPolygonF polygon;
        for (ULONG j = 0; j < getP(); j++) {
            polygon << QPointF(
                    v(f(i, j), 0),
                    -v(f(i, j), 1)
            );
        }
        painter->drawPolygon(polygon);
    }
}

void Polygon::paintWithLighting(QPainter *painter) {
    auto f = sortFaces();
    Matrix v = geom::perProject(applyTr(), 200);
    painter->setPen(Qt::transparent);
    for (ULONG i = 0; i < getF(); i++) {
        QPolygonF polygon;
        std::vector<int> face = f[i];
        for (ULONG j = 0; j < getP(); j++) {
            polygon << QPointF(
                    v(face.at(j), 0),
                    -v(face.at(j), 1)
            );
        }
        painter->setBrush(flatShading(i, face));
        painter->drawPolygon(polygon);
    }
}
