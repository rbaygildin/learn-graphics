//
// Created by Max Heartfield on 03.11.17.
//

#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H


#include <QGraphicsScene>
#include <QJsonObject>
#include <vector>

using namespace std;

class Curve {
public:
    explicit Curve(const vector<QPointF> &anchors);
    virtual void paint(QGraphicsScene* scene) = 0;
    virtual QJsonObject toJson() = 0;
    virtual void addAnchor(const QPointF &anchor) = 0;
    virtual ~Curve() = default;

protected:
    vector<QPointF> anchors;
    vector<QPointF> points;
    QRect bound;
};


#endif //BEZIER_CURVE_H
