//
// Created by Max Heartfield on 14.11.17.
//

#include "affine.h"

namespace geom {

    bool inverse(const Matrix &input, Matrix &inverse)
    {
        typedef permutation_matrix<std::size_t> pmatrix;

        // create a working copy of the input
        Matrix A(input);

        // create a permutation matrix for the LU-factorization
        pmatrix pm(A.size1());

        // perform LU-factorization
        unsigned long res = lu_factorize(A, pm);
        if (res != 0)
            return false;

        // create identity matrix of "inverse"
        inverse.assign(identity_matrix<double> (A.size1()));

        // backsubstitute to get the inverse
        lu_substitute(A, pm, inverse);

        return true;
    }

    Matrix scale(const Matrix &m, double sx, double sy, double sz) {
        Matrix afm(3, 3);
        //first row x
        afm(0, 0) = sx;
        afm(0, 1) = 0;
        afm(0, 2) = 0;
        //second row y
        afm(1, 0) = 0;
        afm(1, 1) = sy;
        afm(1, 2) = 0;
        //third row z - drop
        afm(2, 0) = 0;
        afm(2, 1) = 0;
        afm(2, 2) = sz;
        return trans(prod(afm, trans(m)));
    }

    Matrix translate(const Matrix &m, double dx, double dy, double dz) {
        Matrix afm(4, 4);
        //first row x
        afm(0, 0) = 1;
        afm(0, 1) = 0;
        afm(0, 2) = 0;
        afm(0, 3) = dx;
        //second row y
        afm(1, 0) = 0;
        afm(1, 1) = 1;
        afm(1, 2) = 0;
        afm(1, 3) = dy;
        //third row z - drop
        afm(2, 0) = 0;
        afm(2, 1) = 0;
        afm(2, 2) = 1;
        afm(2, 3) = dz;
        //
        afm(3, 0) = 0;
        afm(3, 1) = 0;
        afm(3, 2) = 0;
        afm(3, 3) = 1;
        Matrix extM(m.size1(), 4);
        for(ULONG r = 0; r < m.size1(); r++){
            for(ULONG c = 0; c < 3; c++){
                extM(r, c) = m(r, c);
            }
            extM(r, 3) = 1;
        }
        Matrix res(m.size1(), 3);
        extM = trans(prod(afm, trans(extM)));
        for(ULONG r = 0; r < m.size1(); r++){
            for(ULONG c = 0; c < 3; c++){
                res(r, c) = extM(r, c);
            }
        }
        return res;
    }

    Matrix rotateX(const Matrix &m, double phi) {
        Matrix afm(3, 3);
        //first row x
        afm(0, 0) = 1;
        afm(0, 1) = 0;
        afm(0, 2) = 0;
        //second row y
        afm(1, 0) = 0;
        afm(1, 1) = cos(phi);
        afm(1, 2) = -sin(phi);
        //third row z - drop
        afm(2, 0) = 0;
        afm(2, 1) = sin(phi);
        afm(2, 2) = cos(phi);
        return trans(prod(afm, trans(m)));
    }

    Matrix rotateY(const Matrix &m, double phi) {
        Matrix afm(3, 3);
        //first row x
        afm(0, 0) = cos(phi);
        afm(0, 1) = 0;
        afm(0, 2) = sin(phi);
        //second row y
        afm(1, 0) = 0;
        afm(1, 1) = 1;
        afm(1, 2) = 0;
        //third row z - drop
        afm(2, 0) = -sin(phi);
        afm(2, 1) = 0;
        afm(2, 2) = cos(phi);
        return trans(prod(afm, trans(m)));
    }

    Matrix rotateZ(const Matrix &m, double phi) {
        Matrix afm(3, 3);
        //first row x
        afm(0, 0) = cos(phi);
        afm(0, 1) = -sin(phi);
        afm(0, 2) = 0;
        //second row y
        afm(1, 0) = sin(phi);
        afm(1, 1) = cos(phi);
        afm(1, 2) = 0;
        //third row z - drop
        afm(2, 0) = 0;
        afm(2, 1) = 0;
        afm(2, 2) = 1;
        return trans(prod(afm, trans(m)));
    }

    Matrix otrProject(const Matrix &m) {
        Matrix pm(3, 3);
        //first row x
        pm(0, 0) = 1;
        pm(0, 1) = 0;
        pm(0, 2) = 0;
        //second row y
        pm(1, 0) = 0;
        pm(1, 1) = 1;
        pm(1, 2) = 0;
        //third row z - drop
        pm(2, 0) = 0;
        pm(2, 1) = 0;
        pm(2, 2) = 0;
        Matrix extM(m.size1(), 4);
        for(ULONG r = 0; r < m.size1(); r++){
            for(ULONG c = 0; c < 3; c++){
                extM(r, c) = m(r, c);
            }
            extM(r, 3) = 1;
        }
        Matrix res(m.size1(), 3);
        extM = trans(prod(pm, trans(extM)));
        for(ULONG r = 0; r < m.size1(); r++){
            for(ULONG c = 0; c < 3; c++){
                res(r, c) = extM(r, c);
            }
        }
        return res;
    }

    Matrix perProject(const Matrix &m, double depth) {
        Matrix pm(4, 4);
        //first row
        pm(0, 0) = 1;
        pm(0, 1) = 0;
        pm(0, 2) = 0;
        pm(0, 3) = 0;
        //second row
        pm(1, 0) = 0;
        pm(1, 1) = 1;
        pm(1, 2) = 0;
        pm(1, 3) = 0;
        //third row
        pm(2, 0) = 0;
        pm(2, 1) = 0;
        pm(2, 2) = 0;
        pm(2, 3) = -1.0 / depth;
        //fourth row
        pm(3, 0) = 0;
        pm(3, 1) = 0;
        pm(3, 2) = 0;
        pm(3, 3) = 1;
        Matrix extM(m.size1(), 4);
        for(ULONG r = 0; r < m.size1(); r++){
            for(ULONG c = 0; c < 3; c++){
                extM(r, c) = m(r, c);
            }
            extM(r, 3) = 1;
        }
        Matrix res(m.size1(), 3);
        Matrix projectedM = trans(prod(pm, trans(extM)));
        for(ULONG r = 0; r < m.size1(); r++){
            double w = projectedM(r, 3);
            for(ULONG c = 0; c < 3; c++){
                res(r, c) = projectedM(r, c) / w;
            }
        }
        return res;
    };

//double get_sign(QGenericMatrix<1, 3, qreal> v, QGenericMatrix<3, 1, qreal> m) {
//    double s;
//    s = v(0, 0) * m(0, 0) + v(0, 1) * m(1, 0) + v(0, 2) * m(2, 0);
//    return s;
//}

}