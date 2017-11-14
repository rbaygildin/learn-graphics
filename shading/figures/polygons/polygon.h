#ifndef IPOLYGON_H
#define IPOLYGON_H

#define FUNCTIONS
#define FIELDS

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QRectF>
#include <QDebug>
#include <QVector3D>
#include <boost/numeric/ublas/matrix.hpp>
#include <cfloat>
#include <cmath>

using namespace boost::numeric::ublas;
using namespace std;

typedef matrix<double> Matrix;
typedef matrix<int> IntMatrix;
typedef unsigned long ULONG;

class Polygon : public QObject, public QGraphicsItem {
Q_OBJECT
public FUNCTIONS:

    explicit Polygon(QObject *parent = 0);

    ~Polygon() override;

    void setEdge(double edge);

    void setCenter(QVector3D center);

    virtual unsigned int getV() const = 0;

    virtual unsigned int getE() const = 0;

    virtual unsigned int getF() const = 0;

    virtual unsigned int getP() const = 0;

    virtual Matrix verteces() const = 0;

    virtual IntMatrix faces() const = 0;

signals:

    void signal1();

protected FUNCTIONS:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private FUNCTIONS:

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected FIELDS:

    double edge;
    QVector3D center;

    //verteces
    static constexpr ULONG V1 = 0;
    static constexpr ULONG V2 = 1;
    static constexpr ULONG V3 = 2;
    static constexpr ULONG V4 = 3;
    static constexpr ULONG V5 = 4;
    static constexpr ULONG V6 = 5;
    static constexpr ULONG V7 = 6;
    static constexpr ULONG V8 = 7;
    static constexpr ULONG V9 = 8;
    static constexpr ULONG V10 = 9;
    static constexpr ULONG V11 = 10;
    static constexpr ULONG V12 = 11;
    //faces
    static constexpr ULONG F1 = 0;
    static constexpr ULONG F2 = 1;
    static constexpr ULONG F3 = 2;
    static constexpr ULONG F4 = 3;
    static constexpr ULONG F5 = 4;
    static constexpr ULONG F6 = 5;
    static constexpr ULONG F7 = 6;
    static constexpr ULONG F8 = 7;
    static constexpr ULONG F9 = 8;
    static constexpr ULONG F10 = 9;
    static constexpr ULONG F11 = 10;
    static constexpr ULONG F12 = 11;
    static constexpr ULONG F13 = 11;
    static constexpr ULONG F14 = 11;
    static constexpr ULONG F15 = 11;
    static constexpr ULONG F16 = 11;
    static constexpr ULONG F17 = 11;
    static constexpr ULONG F18 = 11;
    static constexpr ULONG F19 = 11;
    static constexpr ULONG F20 = 11;
    //p
    static constexpr ULONG P1 = 0;
    static constexpr ULONG P2 = 1;
    static constexpr ULONG P3 = 2;
    static constexpr ULONG P4 = 3;
    static constexpr ULONG P5 = 4;
    //coords
    static constexpr ULONG X = 0;
    static constexpr ULONG Y = 1;
    static constexpr ULONG Z = 2;

};

#endif // IPOLYGON_H
