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
    Matrix v = geom::perProject(applyTr(), 200);
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
//        painter->setBrush(QBrush(flatShading(QColor::fromRgbF(255, 0, 0, 1.0), 1, 10, 0.5, i)));
        painter->drawPolygon(polygon);
    }
    if (isPressed) {
        painter->setPen(Qt::red);
        painter->setBrush(Qt::transparent);
        painter->drawRect(boundingRect());
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Polygon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    isPressed ^= true;
    update();
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

QColor Polygon::flatShading(const QColor &color, double ia, double id, double ka, int faceNumber) {
    QVector3D normal;
    normal.setX(0.0);
    normal.setY(0.0);
    normal.setZ(0.0);
    auto v = applyTr();
    auto f = faces();
    QVector3D a;
    a.setX(v(f(faceNumber, P2), X) - v(f(faceNumber, P1), X));
    a.setY(v(f(faceNumber, P2), Y) - v(f(faceNumber, P1), Y));
    a.setZ(v(f(faceNumber, P2), Z) - v(f(faceNumber, P1), Z));
    QVector3D b;
    b.setX(v(f(faceNumber, P3), X) - v(f(faceNumber, P2), X));
    b.setY(v(f(faceNumber, P3), Y) - v(f(faceNumber, P2), Y));
    b.setZ(v(f(faceNumber, P3), Z) - v(f(faceNumber, P2), Z));
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
    for (int i = 0; i < getP(); i++) {
        xC += v(f(faceNumber, i), X);
        yC += v(f(faceNumber, i), Y);
        zC += v(f(faceNumber, i), Z);
    }
    xC /= getP();
    yC /= getP();
    zC /= getP();
    QVector3D lighter;
    lighter.setX(0);
    lighter.setY(0);
    lighter.setZ(1000);
    n.normalize();
    lighter.normalize();

    double cosinus = QVector3D::dotProduct(n, lighter);
    double ambient = ia * 0.5;
    double diffuse = id * 0.5 * cosinus;
    double res = ambient + diffuse;
    res = res > 1.0 ? 1.0 : res;
    return QColor::fromRgbF(res, res, res, 1.0);
}
