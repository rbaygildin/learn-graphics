//
// Created by Max Heartfield on 08.11.17.
//

#ifndef SEM5_ROBERTS_IFIGURE_H
#define SEM5_ROBERTS_IFIGURE_H

enum ProjectionMode {
    ORT, PER
};

/**
 * Figure interface provides basic api for transformation and drawing
 */
class IFigure {
public:
    virtual IFigure *rotate(double a, double b, double c) = 0;

    virtual IFigure *scale(double a, double b, double c) = 0;

    virtual IFigure *translate(double dx, double dy, double dz) = 0;

    virtual IFigure *parProject() = 0;

    virtual IFigure *perProject(double fov, double far, double near) = 0;

    virtual IFigure *removeHiddenLines(bool flag) = 0;

    virtual void paint() = 0;

    virtual void restore() = 0;

    virtual QRectF bound() = 0;

    virtual QJsonObject toJson() = 0;

    virtual void setSelected(bool isSelected) = 0;
};

#endif //SEM5_ROBERTS_IFIGURE_H
