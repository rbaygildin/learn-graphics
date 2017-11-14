#ifndef TORUS_H
#define TORUS_H

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QRectF>
#include <QDebug>

class Torus : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Torus(QObject *parent = 0);
    ~Torus();
signals:
    void signal1();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TORUS_H
