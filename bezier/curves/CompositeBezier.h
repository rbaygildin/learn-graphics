//
// Created by Max Heartfield on 04.11.17.
//

#ifndef BEZIER_COMPOSITEBEZIERCURVE_H
#define BEZIER_COMPOSITEBEZIERCURVE_H


#include "Curve.h"

class CompositeBezier : public Curve{
public:
    explicit CompositeBezier(const vector<QPointF> &anchors);

};


#endif //BEZIER_COMPOSITEBEZIERCURVE_H
