//
// Created by Max Heartfield on 07.11.17.
//

#include "figure.h"


Figure::Figure(double edge, QGraphicsScene *scene, int V, int E, int F, int P) {
    this->scene = scene;
    this->edge = edge;
    this->V = V;
    this->E = E;
    this->F = F;
    this->P = P;
    hidden = new bool[this->F];
    for (int i = 0; i < this->F; i++) {
        hidden[i] = false;
    }
}

double Figure::rx2sx(double x) {
    double xc = scene->width() / 2;
    return xc + x;
}

double Figure::ry2sy(double y) {
    double yc = scene->height() / 2;
    return yc - y;
}

Figure *Figure::rotate(double a, double b, double c) {
    this->v = Affine::rotate(v, a, b, c);
    return this;
}

Figure *Figure::scale(double a, double b, double c) {
    this->v = Affine::scale(v, a, b, c);
    return this;
}

Figure *Figure::translate(double dx, double dy, double dz) {
    arma::mat m4;
    for (int i = 0; i < V; i++) {
        m4(i, 0) = this->v(i, 0);
        m4(i, 1) = this->v(i, 1);
        m4(i, 2) = this->v(i, 2);
        m4(i, 3) = 1;
    }
    m4 = Affine::translate(m4, dx, dy, dz);
    for (int i = 0; i < V; i++) {
        this->v(i, 0) = m4(i, 0);
        this->v(i, 1) = m4(i, 1);
        this->v(i, 2) = m4(i, 2);
    }
    return this;
}

arma::mat Figure::ortProject() {
    return Affine::ortProject(v);
}

arma::mat Figure::perProject(double depth) {
    arma::mat vExt;
    for (int i = 0; i < F; i++) {
        vExt(i, 0) = v(i, 0);
        vExt(i, 1) = v(i, 1);
        vExt(i, 2) = v(i, 2);
        vExt(i, 3) = 1;
    }
    arma::mat projectedV2 = Affine::perProject(vExt, depth);
    return projectedV2;
}

//Figure* Figure::removeHiddenLines(bool flag) {
//    if(!flag)
//        return this;
//    arma::mat inner;
//    for(int i = 0; i < getV(); i++){
//        inner(0, 0) += v(0, i);
//        inner(1, 0) += v(1, i);
//        inner(2, 0) += v(2, i);
//    }
//    inner(0, 0) /= getV();
//    inner(1, 0) /= getV();
//    inner(2, 0) /= getV();
//    arma::mat d;
//    d(0, 0) = -1;
//    d(0, 1) = -1;
//    d(0, 2) = -1;
//    arma::mat view;
//    view(0, 0) = 0;
//    view(1, 0) = 0;
//    view(2, 0) = -600000;
//    for (int i = 0; i < getF(); i++) {
//        arma::mat x;
//        for(int vj = 0; vj < 3; vj++){
//            x(0, vj) = v(0, f(vj, i));
//            x(1, vj) = v(1, f(vj, i));
//            x(2, vj) = v(2, f(vj, i));
//        }
//        arma::mat coeff = d * inv(x);
//        double sign = Affine::getSign(inner, coeff) + 1;
//        double sign2 = Affine::getSign(view, coeff) + 1;
//        hidden[i] = sign * sign2 >= 0;
//    }
//    return this;
//}

void Figure::paint(ProjMode projMode) {
    QPen pen(Qt::black);
    QBrush brush(Qt::white);
    pen.setWidth(3);
    arma::mat pV;
    if (projMode == ProjMode::ORT)
        pV = ortProject();
    else
        pV = perProject(0);
    for (int i = 0; i < F; i++) {
        if (hidden[i])
            continue;
        QPolygonF face;
        for (int j = 0; j < P; j++) {
            qreal x = rx2sx(pV(f(i, j), 0));
            qreal y = ry2sy(pV(f(i, j), 1));
            face << QPointF(
                    x, y
            );
        }
        scene->addPolygon(face, pen);
    }
}

Figure::~Figure() {
    delete hidden;
}
