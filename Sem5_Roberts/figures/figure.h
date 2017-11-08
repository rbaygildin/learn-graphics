//
// Created by Roman Yarnykh on 31.10.17.
//

#ifndef SEM5_ROBERTS_FIGURE_H
#define SEM5_ROBERTS_FIGURE_H


#include <QGraphicsScene>
#include <QGenericMatrix>
#include "../affine.h"
#include "ifigure.h"

#define X 0
#define Y 1
#define Z 2

#define PI 3.1459

template<int V, int E, int F, int P>
class Figure : public IFigure {
public:
    Figure(double edge, QGraphicsScene *scene);

public:
    Figure *rotate(double a, double b, double c) override;

    Figure *scale(double a, double b, double c) override;

    Figure *translate(double dx, double dy, double dz) override;

    Figure *parProject() override;

    Figure *perProject(double fov, double far, double near) override;

    Figure<V, E, F, P> *removeHiddenLines(bool flag) override;

    void paint(bool roberts = false, ProjectionMode mode = ProjectionMode::ORT);

    void restore() override;

    void setSelected(bool isSelected) {
        this->isSelected = isSelected;
    }

protected:
    virtual QGenericMatrix<V, 3, qreal> vertex() = 0;

    virtual QGenericMatrix<F, P, qreal> faces() = 0;

protected:
    double rx2sx(double x);

    double ry2sy(double y);

protected:
    bool isRemoveLines = false;
    QGraphicsScene *scene;
    QGenericMatrix<V, 3, qreal> originalV;
    QGenericMatrix<V, 3, qreal> v;
    QGenericMatrix<V, 3, qreal> pV;
    QGenericMatrix<F, P, qreal> f;
    bool hidden[F];
    double edge;
    bool isSelected = false;
};


template<int V, int E, int F, int P>
Figure<V, E, F, P>::Figure(double edge, QGraphicsScene *scene) {
    this->scene = scene;
    this->edge = edge;
    for (int i = 0; i < F; i++) {
        hidden[i] = false;
    }
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
Figure<V, E, F, P> *Figure<V, E, F, P>::rotate(double a, double b, double c) {
    this->originalV = rotationXMatrix(a) * rotationYMatrix(b) * rotationZMatrix(c) * this->originalV;
    return this;
}

template<int V, int E, int F, int P>
Figure<V, E, F, P> *Figure<V, E, F, P>::scale(double a, double b, double c) {
    this->originalV = scaleMatrix(a, b, c) * this->originalV;
    return this;
}

template<int V, int E, int F, int P>
Figure<V, E, F, P> *Figure<V, E, F, P>::translate(double dx, double dy, double dz) {
    QGenericMatrix<V, 4, qreal> m4;
    for (int i = 0; i < V; i++) {
        m4(0, i) = this->originalV(0, i);
        m4(1, i) = this->originalV(1, i);
        m4(2, i) = this->originalV(2, i);
        m4(3, i) = 1;
    }
    m4 = translationMatrix(dx, dy, dz).transposed() * m4;
    for (int i = 0; i < V; i++) {
        this->originalV(0, i) = m4(0, i);
        this->originalV(1, i) = m4(1, i);
        this->originalV(2, i) = m4(2, i);
    }
    return this;
}

template<int V, int E, int F, int P>
Figure<V, E, F, P> *Figure<V, E, F, P>::parProject() {
    QGenericMatrix<3, 3, qreal> proj = otrProjectionMatrix();
    pV = proj * originalV;
    return this;
}

template<int V, int E, int F, int P>
Figure<V, E, F, P> *Figure<V, E, F, P>::perProject(double fov, double far, double near) {
    QGenericMatrix<4, 4, qreal> proj = perProjectionMatrix(fov, far, near);
    QGenericMatrix<V, 4, qreal> vExt;
    for (int i = 0; i < V; i++) {
        vExt(0, i) = originalV(0, i);
        vExt(1, i) = originalV(1, i);
        vExt(2, i) = originalV(2, i);
        vExt(3, i) = 1;
    }
    QGenericMatrix<V, 4, qreal> projectedV2 = proj * vExt;
    for (int i = 0; i < V; i++) {
        if(abs(projectedV2(3, i) - 1.0) >= 0.01) {
            projectedV2(0, i) /= projectedV2(3, i);
            projectedV2(1, i) /= projectedV2(3, i);
        }
        pV(0, i) = projectedV2(0, i);
        pV(1, i) = projectedV2(1, i);
    }
    return this;
}

template<int V, int E, int F, int P>
Figure<V, E, F, P> *Figure<V, E, F, P>::removeHiddenLines(bool flag) {
    if (!flag)
        return this;
    QGenericMatrix<1, 3, qreal> inner;
    inner.fill(0);
    for (int i = 0; i < V; i++) {
        inner(0, 0) += originalV(0, i);
        inner(1, 0) += originalV(1, i);
        inner(2, 0) += originalV(2, i);
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
            x(0, vj) = originalV(0, f(vj, i));
            x(1, vj) = originalV(1, f(vj, i));
            x(2, vj) = originalV(2, f(vj, i));
        }
        QGenericMatrix<3, 1, qreal> coeff = d * inverseMatrix(x);
        double sign = get_sign(inner, coeff) + 1;
        double sign2 = get_sign(view, coeff) + 1;
        hidden[i] = sign * sign2 >= 0;
    }
    return this;
}

template<int V, int E, int F, int P>
void Figure<V, E, F, P>::paint(bool roberts, ProjectionMode mode) {
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    pen.setWidth(3);
    for (int i = 0; i < F; i++) {
        if (hidden[i])
            continue;
        QPolygonF face;
        for (int j = 0; j < P; j++) {
            face << QPointF(
                    rx2sx(pV(0, f(j, i))),
                    ry2sy(pV(1, f(j, i)))
            );
        }
        scene->addPolygon(face, pen);
    }
    if (isSelected)
        scene->addRect(bound(), QPen(Qt::red));
}

template<int V, int E, int F, int P>
void Figure<V, E, F, P>::restore() {
    this->originalV = this->v;
}


#endif //SEM5_ROBERTS_FIGURE_H
