//
// Created by Max Heartfield on 14.11.17.
//

#include "common.h"

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

double slider2degree(int slider){
    return (slider - 50) * 2;
}

double slider2scale(int slider){
    return (slider * 1.0 + 1.0) / 20.0;
}

double degree2radian(double d){
    return d * M_PI / 180.0;
}

