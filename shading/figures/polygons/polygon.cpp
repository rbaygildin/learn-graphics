#include "polygon.h"

Polygon::Polygon(QObject *parent)
{

}

Polygon::~Polygon(){

}

QRectF Polygon::boundingRect() const{

    return QRectF(-50, 0, 50, 50);
}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    IntMatrix f = faces();
    Matrix v = verteces();
    painter->setBrush(Qt::blue);
    painter->setPen(Qt::black);
    for (int i = 0; i < getF(); i++) {
        QPolygonF face;
        for (int j = 0; j < getP(); j++) {
            face << QPointF(
                    v(f(i, j), 0),
                    v(f(i, j), 1)
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

void Polygon::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit signal1();
    QGraphicsItem::mousePressEvent(event);
}

void Polygon::setEdge(double edge) {
    this->edge = edge;
}

void Polygon::setCenter(QVector3D center) {
    this->center = center;
}
