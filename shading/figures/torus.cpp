#include "torus.h"

Torus::Torus(QObject *parent)
{

}

Torus::~Torus(){

}

QRectF Torus::boundingRect() const{
    return QRectF(0, 0, 100, 100);
}

void Torus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush(Qt::blue);
    painter->drawEllipse(QRectF(0, 0, 100, 100));
}

void Torus::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit signal1();
    QGraphicsItem::mousePressEvent(event);
}
