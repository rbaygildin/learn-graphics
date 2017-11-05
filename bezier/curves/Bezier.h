//
// Created by Max Heartfield on 03.11.17.
//

#ifndef BEZIER_BEZIERCURVE_H
#define BEZIER_BEZIERCURVE_H


#include <QGraphicsScene>
#include <vector>
#include "Curve.h"

class Bezier : public Curve{
public:
    explicit Bezier(const vector<QPointF> &anchors);
    void paint(QGraphicsScene* scene) override;
    QJsonObject toJson() override;
    void addAnchor(const QPointF &point) override;
    static Bezier fromJson(const QJsonObject& json);
private:
    vector<QPointF> casteljau();
    vector<QPointF> order1();
    vector<QPointF> order2();
    vector<QPointF> order3();

private:
    vector<QPointF> points;
    static constexpr auto DELTA = 0.02;
    static constexpr auto R = 10;
};


#endif //BEZIER_BEZIERCURVE_H
