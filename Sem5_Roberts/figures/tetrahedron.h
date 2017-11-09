//
// Created by Max Heartfield on 09.11.17.
//

#ifndef SEM5_ROBERTS_TETRAHEDRON_H
#define SEM5_ROBERTS_TETRAHEDRON_H

#include <QRectF>
#include <QJsonObject>
#include <QJsonArray>
#include <QGenericMatrix>
#include <QPen>
#include <QBrush>
#include <QGraphicsScene>
#include <vector>
#include "ifigure.h"
#include "pointf3d.h"
#include "../affine.h"

using namespace std;

class Tetrahedron : public IFigure {
public:
    Tetrahedron(QGraphicsScene *scene, PointF3d v1, PointF3d v2, PointF3d v3, PointF3d v4) : IFigure() {
        //v1
        v(0, 0) = v1.x;
        v(1, 0) = v1.y;
        v(2, 0) = v1.z;
        //v2
        v(0, 1) = v2.x;
        v(1, 1) = v2.y;
        v(2, 1) = v2.z;
        //v3
        v(0, 2) = v3.x;
        v(1, 2) = v3.y;
        v(2, 2) = v3.z;
        //v4
        v(0, 3) = v4.x;
        v(1, 3) = v4.y;
        v(2, 3) = v4.z;
        //f1 - bottom
        f(0, 0) = 0;
        f(1, 0) = 1;
        f(2, 0) = 2;
        //f2 - right
        f(0, 1) = 0;
        f(1, 1) = 1;
        f(2, 1) = 3;
        //f3 - back
        f(0, 2) = 1;
        f(1, 2) = 2;
        f(2, 2) = 3;
        //f4 - left
        f(0, 3) = 2;
        f(1, 3) = 0;
        f(2, 3) = 3;
        xC = (v(0, 0) + v(0, 1) + v(0, 2)) / 3;
        yC = (v(1, 0) + v(1, 1) + v(1, 2)) / 3;
        zC = (v(2, 0) + v(2, 1) + v(2, 2)) / 3;
        this->scene = scene;
    }

    void paint(bool isRemoveLines) override {
        QPen pen(Qt::black);
        QBrush brush(Qt::white);
        pen.setWidth(3);
        QGenericMatrix<4, 3, qreal> resV = rotate(v, transformations[RotateX], transformations[RotateY],
                                                  transformations[RotateZ]);
        resV = scale(resV, transformations[ScaleX], transformations[ScaleY], transformations[ScaleZ]);
        resV = translate(resV, transformations[TranslateX], transformations[TranslateY], transformations[TranslateZ]);
        vector<bool> hidden = removeLines(isRemoveLines, v, f, -6000);
        QGenericMatrix<4, 3, qreal> projV = parProject(resV);
        for (int i = 0; i < F; i++) {
            if (hidden[i])
                continue;
            QPolygonF face;
            for (int j = 0; j < P; j++) {
                face << QPointF(
                        rx2sx(projV(0, f(j, i))),
                        ry2sy(projV(1, f(j, i)))
                );
            }
            scene->addPolygon(face, pen);
        }
    }

    void paint(bool isRemoveLines, double fov, double near, double far, double aspectRatio) override {
        QPen pen(Qt::black);
        QBrush brush(Qt::white);
        pen.setWidth(3);
        QGenericMatrix<4, 3, qreal> resV = rotate(v, transformations[RotateX], transformations[RotateY],
                                                  transformations[RotateZ]);
        resV = scale(resV, transformations[ScaleX], transformations[ScaleY], transformations[ScaleZ]);
        resV = translate(resV, transformations[TranslateX], transformations[TranslateY], transformations[TranslateZ]);
        vector<bool> hidden = removeLines(isRemoveLines, v, f, fov);
        QGenericMatrix<4, 4, qreal> projV = perProject(resV, fov, near, far, aspectRatio);
        for (int i = 0; i < F; i++) {
            if (hidden[i])
                continue;
            QPolygonF face;
            for (int j = 0; j < P; j++) {
                face << QPointF(
                        rx2sx(projV(0, f(j, i))),
                        ry2sy(projV(1, f(j, i)))
                );
            }
            scene->addPolygon(face, pen);
        }
    }

    void restore() override {
        transformations[ScaleX] = 1.0;
        transformations[ScaleY] = 1.0;
        transformations[ScaleZ] = 1.0;
        transformations[RotateX] = 0.0;
        transformations[RotateY] = 0.0;
        transformations[RotateZ] = 0.0;
        transformations[TranslateX] = 0.0;
        transformations[TranslateY] = 0.0;
        transformations[TranslateZ] = 0.0;
    }

    QRectF bound() override {
        return QRect();
    }

    QJsonObject toJson() override {
        QJsonObject json;
        json["type"] = "TETRAHEDRON";
        QJsonArray array;
        for (int i = 0; i < 9; i++) {
            array.push_back(transformations[i]);
        }
        json.insert("transformations", array);
        QJsonArray vertexArray;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < 3; j++) {
                vertexArray.push_back(v(j, i));
            }
        }
        json.insert("vertex", vertexArray);
        return json;
    }

    void setSelected(bool isSelected) override {

    }

    double zIndex() override {
        return zC;
    }

private:
    double rx2sx(double x) {
        double xc = scene->width() / 2;
        return xc + x;
    }


    double ry2sy(double y) {
        double yc = scene->height() / 2;
        return yc - y;
    }

    QGenericMatrix<4, 3, qreal> rotate(QGenericMatrix<4, 3, qreal> v2, double a, double b, double c) {
        return rotationXMatrix(a) * rotationYMatrix(b) * rotationZMatrix(c) * v2;
    }

    QGenericMatrix<4, 3, qreal> scale(QGenericMatrix<4, 3, qreal> v2, double a, double b, double c) {
        return scaleMatrix(a, b, c) * v2;
    }

    QGenericMatrix<4, 3, qreal> translate(QGenericMatrix<4, 3, qreal> v2, double dx, double dy, double dz) {
        QGenericMatrix<4, 4, qreal> m4;
        for (int i = 0; i < V; i++) {
            m4(0, i) = v2(0, i);
            m4(1, i) = v2(1, i);
            m4(2, i) = v2(2, i);
            m4(3, i) = 1;
        }
        QGenericMatrix<4, 3, qreal> res;
        m4 = translationMatrix(dx, dy, dz).transposed() * m4;
        for (int i = 0; i < V; i++) {
            res(0, i) = m4(0, i);
            res(1, i) = m4(1, i);
            res(2, i) = m4(2, i);
        }
        return res;
    }

    QGenericMatrix<4, 3, qreal> parProject(QGenericMatrix<4, 3, qreal> v2) {
        QGenericMatrix<3, 3, qreal> proj = otrProjectionMatrix();
        return proj * v2;
    }

    QGenericMatrix<4, 4, qreal>
    perProject(QGenericMatrix<4, 3, qreal> v2, double fov, double near, double far, double aspectRatio) {
        QGenericMatrix<4, 4, qreal> proj = perProjectionMatrix(fov, near, far, aspectRatio);
        QGenericMatrix<4, 4, qreal> vExt;
        for (int i = 0; i < V; i++) {
            vExt(0, i) = v2(0, i);
            vExt(1, i) = v2(1, i);
            vExt(2, i) = v2(2, i);
            vExt(3, i) = 1;
        }
        QGenericMatrix<4, 4, qreal> projectedV2 = proj * vExt;
        for (int i = 0; i < V; i++) {
            double p = projectedV2(3, i);
            if (abs(p - 1.0) >= 0.01) {
                double x = projectedV2(0, i) / p;
                double y = projectedV2(1, i) / p;
                projectedV2(0, i) = x;
                projectedV2(1, i) = y;
            }
        }
        return projectedV2;
    }

    vector<bool>
    removeLines(bool isRemoveLines, QGenericMatrix<4, 3, qreal> v2, QGenericMatrix<4, 3, int> f2, double z0) {
        vector<bool> hidden;
        for (int i = 0; i < F; i++) {
            hidden.push_back(false);
        }
        if (!isRemoveLines)
            return hidden;
        QGenericMatrix<1, 3, qreal> inner;
        inner.fill(0);
        for (int i = 0; i < V; i++) {
            inner(0, 0) += v2(0, i);
            inner(1, 0) += v2(1, i);
            inner(2, 0) += v2(2, i);
        }
        inner(0, 0) /= V;
        inner(1, 0) /= V;
        inner(2, 0) /= V;
        QGenericMatrix<3, 1, qreal> d;
        d(0, 0) = -1;
        d(0, 1) = -1;
        d(0, 2) = -1;
        QGenericMatrix<1, 3, qreal> view;
        view(0, 0) = 0;
        view(1, 0) = 0;
        view(2, 0) = z0;
        for (int i = 0; i < F; i++) {
            QGenericMatrix<3, 3, qreal> x;
            for (int vj = 0; vj < 3; vj++) {
                x(0, vj) = v2(0, f2(vj, i));
                x(1, vj) = v2(1, f2(vj, i));
                x(2, vj) = v2(2, f2(vj, i));
            }
            QGenericMatrix<3, 1, qreal> coeff = d * inverseMatrix(x);
            for(int ci = 0; ci < 3; ci++)
                coeff(0, ci) = coeff(0, ci) < 0 ? -coeff(0, ci) : coeff(0, ci);
            double sign = get_sign(inner, coeff) + 1;
            double sign2 = get_sign(view, coeff) + 1;
            hidden[i] = sign2 < 0;
        }
        return hidden;
    }

private:
    static constexpr auto V = 4;
    static constexpr auto F = 4;
    static constexpr auto P = 3;
    double xC;
    double yC;
    double zC;
    QGenericMatrix<4, 3, qreal> v;
    QGenericMatrix<F, P, int> f;
    QGraphicsScene *scene;
};

#endif //SEM5_ROBERTS_TETRAHEDRON_H
