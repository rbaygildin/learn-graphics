//
// Created by Roman Yarnykh on 31.10.17.
//

#ifndef SEM5_ROBERTS_FIGURE_H
#define SEM5_ROBERTS_FIGURE_H


#include <QGraphicsScene>
#include <QJsonArray>
#include <QVector3D>
#include <QGenericMatrix>
#include <vector>
#include "../affine.h"
#include "ifigure.h"

#define X 0
#define Y 1
#define Z 2

#define PI 3.1459

using namespace std;

template<int V, int E, int F, int P>
class Figure : public IFigure {
public:
    Figure(double edge, QGraphicsScene *scene);

public:

    void paint(bool isRemoveLines) final;

    void paint(bool isRemoveLines, double far, double near, double fov) final;

    void restore() final;

    void setSelected(bool isSelected) final {
    }

    double zIndex() {
        return zC;
    }

    virtual QJsonObject toJson(){
        QJsonObject json;
        json.insert("edge", edge);
        QJsonArray array;
        for(int i = 0; i < 9; i++) {
            array.push_back(transformations[i]);
        }
        json.insert("transformations", array);
        return json;
    }

protected:
    vector<bool> removeLines(bool isRemoveLines, QGenericMatrix<V, 3, qreal> v2, QGenericMatrix<F, P, qreal> f2);

    QGenericMatrix<V, 3, qreal> rotate(QGenericMatrix<V, 3, qreal> v2, double a, double b, double c);

    QGenericMatrix<V, 3, qreal> scale(QGenericMatrix<V, 3, qreal> v2, double a, double b, double c);

    QGenericMatrix<V, 3, qreal> translate(QGenericMatrix<V, 3, qreal> v2, double dx, double dy, double dz);

    QGenericMatrix<V, 3, qreal> parProject(QGenericMatrix<V, 3, qreal> v2);

    QGenericMatrix<V, 4, qreal> perProject(QGenericMatrix<V, 3, qreal> v2, double fov, double far, double near);

    virtual QGenericMatrix<V, 3, qreal> vertex() = 0;

    virtual QGenericMatrix<F, P, qreal> faces() = 0;

protected:
    double rx2sx(double x);

    double ry2sy(double y);

protected:
    QGraphicsScene *scene;
    QGenericMatrix<V, 3, qreal> v;
    QGenericMatrix<V, 3, qreal> originalV;
    QGenericMatrix<V, 3, qreal> pV;
    QGenericMatrix<F, P, qreal> f;
    double edge;
    double xC;
    double yC;
    double zC;
};


template<int V, int E, int F, int P>
Figure<V, E, F, P>::Figure(double edge, QGraphicsScene *scene) {
    this->scene = scene;
    this->edge = edge;
}

template<int V, int E, int F, int P>
double Figure<V, E, F, P>::rx2sx(double x) {
    double xc = scene->width() / 2;
    return xc + x;
}

template<int V, int E, int F, int P>
double Figure<V, E, F, P>::ry2sy(double y) {
    double yc = scene->height() / 2;
    return yc - y;
}

template<int V, int E, int F, int P>
QGenericMatrix<V, 3, qreal> Figure<V, E, F, P>::rotate(QGenericMatrix<V, 3, qreal> v2, double a, double b, double c) {
    return rotationXMatrix(a) * rotationYMatrix(b) * rotationZMatrix(c) * v2;
}

template<int V, int E, int F, int P>
QGenericMatrix<V, 3, qreal> Figure<V, E, F, P>::scale(QGenericMatrix<V, 3, qreal> v2, double a, double b, double c) {
    return scaleMatrix(a, b, c) * v2;
}

template<int V, int E, int F, int P>
QGenericMatrix<V, 3, qreal> Figure<V, E, F, P>::translate(QGenericMatrix<V, 3, qreal> v2, double dx, double dy, double dz) {
    QGenericMatrix<V, 4, qreal> m4;
    for (int i = 0; i < V; i++) {
        m4(0, i) = v2(0, i);
        m4(1, i) = v2(1, i);
        m4(2, i) = v2(2, i);
        m4(3, i) = 1;
    }
    QGenericMatrix<V, 3, qreal> res;
    m4 = translationMatrix(dx, dy, dz).transposed() * m4;
    for (int i = 0; i < V; i++) {
        res(0, i) = m4(0, i);
        res(1, i) = m4(1, i);
        res(2, i) = m4(2, i);
    }
    return res;
}

template<int V, int E, int F, int P>
QGenericMatrix<V, 3, qreal> Figure<V, E, F, P>::parProject(QGenericMatrix<V, 3, qreal> v2) {
    QGenericMatrix<3, 3, qreal> proj = otrProjectionMatrix();
    return proj * v2;
}

template<int V, int E, int F, int P>
QGenericMatrix<V, 4, qreal> Figure<V, E, F, P>::perProject(QGenericMatrix<V, 3, qreal> v2, double fov, double far, double near) {
    QGenericMatrix<4, 4, qreal> proj = perProjectionMatrix(fov, far, near);
    QGenericMatrix<V, 4, qreal> vExt;
    for (int i = 0; i < V; i++) {
        vExt(0, i) = v2(0, i);
        vExt(1, i) = v2(1, i);
        vExt(2, i) = v2(2, i);
        vExt(3, i) = 1;
    }
    QGenericMatrix<V, 4, qreal> projectedV2 = proj * vExt;
    QGenericMatrix<V, 2, qreal> res;
    for (int i = 0; i < V; i++) {
        if (abs(projectedV2(3, i) - 1.0) >= 0.01) {
            projectedV2(0, i) /= projectedV2(3, i);
            projectedV2(1, i) /= projectedV2(3, i);
        }
        res(0, i) = projectedV2(0, i);
        res(1, i) = projectedV2(1, i);
    }
    return projectedV2;
}

template<int V, int E, int F, int P>
vector<bool> Figure<V, E, F, P>::removeLines(bool isRemoveLines, QGenericMatrix<V, 3, qreal> v2, QGenericMatrix<F, P, qreal> f2) {
    vector<bool> hidden;
    for (int i = 0; i < F; i++) {
        hidden.push_back(false);
    }
    if(!isRemoveLines)
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
    view(2, 0) = -600000;
    for (int i = 0; i < F; i++) {
        QGenericMatrix<3, 3, qreal> x;
        for (int vj = 0; vj < 3; vj++) {
            x(0, vj) = v2(0, f2(vj, i));
            x(1, vj) = v2(1, f2(vj, i));
            x(2, vj) = v2(2, f2(vj, i));
        }
        QGenericMatrix<3, 1, qreal> coeff = d * inverseMatrix(x);
        double sign = get_sign(inner, coeff) + 1;
        double sign2 = get_sign(view, coeff) + 1;
        hidden[i] = sign * sign2 >= 0;
    }
    return hidden;
}

template<int V, int E, int F, int P>
void Figure<V, E, F, P>::paint(bool isRemoveLines) {
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    pen.setWidth(3);
    QGenericMatrix<V, 3, qreal> resV = rotate(v, transformations[RotateX], transformations[RotateY], transformations[RotateZ]);
    resV = scale(resV, transformations[ScaleX], transformations[ScaleY], transformations[ScaleZ]);
    resV = translate(resV, transformations[TranslateX], transformations[TranslateY], transformations[TranslateZ]);
    vector<bool> hidden = removeLines(isRemoveLines, v, f);
    QGenericMatrix<V, 3, qreal> projV = parProject(resV);
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

template<int V, int E, int F, int P>
void Figure<V, E, F, P>::paint(bool removeLines, double far, double near, double fov) {

}

template<int V, int E, int F, int P>
void Figure<V, E, F, P>::restore() {
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


#endif //SEM5_ROBERTS_FIGURE_H
