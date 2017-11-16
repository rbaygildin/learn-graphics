//
// Created by Max Heartfield on 14.11.17.
//

#ifndef PLANE3D_COMMON_H
#define PLANE3D_COMMON_H

#define functions
#define fields

#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

typedef unsigned long ULONG;
typedef matrix<double> Matrix;
typedef matrix<ULONG> IntMatrix;

template<typename Base, typename T>
inline bool instanceof(const T *ptr);

double slider2degree(int slider);

double slider2scale(int slider);

double degree2radian(double d);

#endif //PLANE3D_COMMON_H
