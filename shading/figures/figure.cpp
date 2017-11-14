//
// Created by Max Heartfield on 14.11.17.
//

#include "figure.h"

Figure::Figure(QObject *parent) : QObject(parent) {
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

Figure::~Figure() {

}

void Figure::transform(int operation, double value) {
    transformations[operation] = value;
}

void Figure::identityTransform() {
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
