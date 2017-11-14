//
// Created by Max Heartfield on 14.11.17.
//

#ifndef PLANE3D_FIGURE_H
#define PLANE3D_FIGURE_H


#include <QObject>
#include <QGraphicsItem>
#include "../common.h"

class Figure : public QObject, public QGraphicsItem {
Q_OBJECT
public functions:
    explicit Figure(QObject *parent = nullptr);

    ~Figure() override;

    virtual QJsonObject toJson() const = 0;

    virtual void transform(int operation, double value);

signals:

    void signal1();

protected fields:
    double transformations[9]{};
    static constexpr auto ScaleX = 0;
    static constexpr auto ScaleY = 1;
    static constexpr auto ScaleZ = 2;
    static constexpr auto RotateX = 3;
    static constexpr auto RotateY = 4;
    static constexpr auto RotateZ = 5;
    static constexpr auto TranslateX = 6;
    static constexpr auto TranslateY = 7;
    static constexpr auto TranslateZ = 8;

};


#endif //PLANE3D_FIGURE_H
