//
// Created by Max Heartfield on 14.11.17.
//

#ifndef PLANE3D_FIGURE_H
#define PLANE3D_FIGURE_H


#include <QObject>
#include <QGraphicsItem>
#include <QVector3D>
#include "../common.h"

class Figure : public QObject, public QGraphicsItem {
Q_OBJECT

public functions:

    explicit Figure(QObject *parent = nullptr);

    ~Figure() override;

    virtual QJsonObject toJson() const = 0;

    virtual void transform(int operation, double value);

    virtual void identityTransform();

signals:

    void signal1();

public slots:
    void setMeshMode();
    void setWithLightingMode();
    void setColor(QColor color);
    void setAmbient(int tick);
    void setDiffuse(int tick);
    void setLampX(int tick);
    void setLampY(int tick);
    void setLampZ(int tick);

protected functions:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void paintMesh(QPainter *painter) = 0;
    virtual void paintWithLighting(QPainter *painter) = 0;
    void setLightingOptions(const QColor &color, double ia, double ka, double id, double kd, QVector3D lamp);
    QColor shade(QVector3D n);

public fields:
    static constexpr auto ScaleX = 0;
    static constexpr auto ScaleY = 1;
    static constexpr auto ScaleZ = 2;
    static constexpr auto RotateX = 3;
    static constexpr auto RotateY = 4;
    static constexpr auto RotateZ = 5;
    static constexpr auto TranslateX = 6;
    static constexpr auto TranslateY = 7;
    static constexpr auto TranslateZ = 8;
    static constexpr auto MESH = 0;
    static constexpr auto WITH_LIGHTING = 1;
    bool isChosen = false;

protected fields:
    double transformations[9]{};
    QColor color;
    double ia, ka, id, kd;
    QVector3D lamp;
    int mode = MESH;
};


#endif //PLANE3D_FIGURE_H
