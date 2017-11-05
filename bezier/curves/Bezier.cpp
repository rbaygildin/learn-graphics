//
// Created by Max Heartfield on 03.11.17.
//

#include <QJsonObject>
#include <QJsonArray>
#include "Bezier.h"

void Bezier::paint(QGraphicsScene *scene) {
    QPen pen(Qt::black);
    QBrush brush(Qt::red);
    for (auto &anchor : anchors) {
        scene->addEllipse(anchor.x(), anchor.y(), Bezier::R, Bezier::R, pen, brush);
    }
    if(anchors.size() <= 1)
        return;
    QPointF prev(points[0]);
    for (int i = 1; i < points.size(); i++) {
        scene->addLine(prev.x(), prev.y(), points[i].x(), points[i].y(), pen);
        prev = points[i];
    }
}

QJsonObject Bezier::toJson() {
    QJsonObject json;
    json["type"] = "BEZIER";
    QJsonArray points;
    for (auto &anchor : anchors) {
        QJsonObject point;
        point["x"] = anchor.x();
        point["y"] = anchor.y();
        points.append(point);
    }
    json["anchors"] = points;
    return json;
}

Bezier::Bezier(const vector<QPointF> &anchors) : Curve(anchors) {}

Bezier Bezier::fromJson(const QJsonObject &json) {
    QJsonArray points = json["anchors"].toArray();
    vector<QPointF> anchors;
    for (auto point : points) {
        QPointF anchor(point.toObject()["x"].toInt(), point.toObject()["y"].toInt());
        anchors.push_back(anchor);
    }
    return Bezier(anchors);
}

vector<QPointF> Bezier::casteljau() {
    vector<QPointF> curve;
    long n = anchors.size();
    for (double t = 0.0; t <= 1.0; t += DELTA) {
        auto **b = new QPointF*[n];
        for (int i = 0; i < n; i++)
        {
            b[i] = new QPointF[n];
        }
        for (int i = 0; i < n; i++)
        {
            b[0][i] = anchors[i];
        }
        for (int j = 1; j < n; j++) {
            for (int i = 0; i < n - j; i++) {
                b[j][i].setX((1 - t) * b[j - 1][i].x() + t * b[j - 1][i + 1].x());
                b[j][i].setY((1 - t) * b[j - 1][i].y() + t * b[j - 1][i + 1].y());
            }
        }
        curve.emplace_back(b[n - 1][0]);
        for(int i = 0; i < n; i++)
            delete b[i];
        delete b;
    }
    curve.emplace_back(anchors[n - 1].x(),
                       anchors[n - 1].y()
    );
    return curve;
}

void Bezier::addAnchor(const QPointF &point) {
    anchors.emplace_back(point);
    if (anchors.size() <= 1)
        return;
    if (anchors.size() == 2)
        points = order1();
    else if (anchors.size() == 3)
        points = order2();
    else if (anchors.size() == 4)
        points = order3();
    else
        points = casteljau();
}

vector<QPointF> Bezier::order1() {
    vector<QPointF> curve;
    for (double t = 0.0; t < 1.0; t += DELTA) {
        curve.emplace_back((1.0 - t) * anchors[0].x() + t * anchors[1].x(),
                           (1.0 - t) * anchors[0].y() + t * anchors[1].y()
        );
    }
    curve.emplace_back(anchors[1].x(),
                       anchors[1].y());
    return curve;
}

vector<QPointF> Bezier::order2() {
    vector<QPointF> curve;
    for (double t = 0.0; t < 1.0; t += DELTA) {
        double x = (1.0 - t) * (1.0 - t) * anchors[2].x() + 2 * (1.0 - t) * t * anchors[1].x() + t * t * anchors[0].x();
        double y = (1.0 - t) * (1.0 - t) * anchors[2].y() + 2 * (1.0 - t) * t * anchors[1].y() + t * t * anchors[0].y();
        curve.emplace_back(QPointF(x, y));
    }
    curve.emplace_back(anchors[0].x(),
                       anchors[0].y()
    );
    return curve;
}

vector<QPointF> Bezier::order3() {
    vector<QPointF> curve;
    for (double t = 0; t < 1; t += DELTA) {
        double x = (1.0 - t) * (1.0 - t) * (1.0 - t) * anchors[0].x() +
                   3 * (1.0 - t) * (1.0 - t) * t * anchors[1].x() +
                   3 * (1 - t) * t * t * anchors[2].x() +
                   t * t * t * anchors[3].x();
        double y = (1.0 - t) * (1.0 - t) * (1.0 - t) * anchors[0].y() +
                   3 * (1.0 - t) * (1.0 - t) * t * anchors[1].y() +
                   3 * (1.0 - t) * t * t * anchors[2].y() +
                   t * t * t * anchors[3].y();
        curve.emplace_back(QPointF(x, y));
    }
    curve.emplace_back(QPointF(
            anchors[3].x(),
            anchors[3].y()
    ));
    return curve;
}
