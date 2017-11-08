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
    static constexpr auto ScaleX = 0;
    static constexpr auto ScaleY = 1;
    static constexpr auto ScaleZ = 2;
    static constexpr auto RotateX = 3;
    static constexpr auto RotateY = 4;
    static constexpr auto RotateZ = 5;
    static constexpr auto TranslateX = 6;
    static constexpr auto TranslateY = 7;
    static constexpr auto TranslateZ = 8;
public:
    IFigure(){
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
public:
    virtual IFigure *transform(int operation, double value){
        transformations[operation] = value;
        return this;
    }

    virtual void paint(bool removeLines) = 0;

    virtual void paint(bool removeLines, double far, double near, double fov) = 0;

    virtual void restore() = 0;

    virtual QRectF bound() = 0;

    virtual QJsonObject toJson() = 0;

    virtual void setSelected(bool isSelected) = 0;

    virtual double zIndex() = 0;

protected:
    double transformations[9]{};
};

#endif //SEM5_ROBERTS_IFIGURE_H
