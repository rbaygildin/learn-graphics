//
// Created by Max Heartfield on 11.03.18.
//

#ifndef OPENGL_DICOMUTILS_H
#define OPENGL_DICOMUTILS_H


#include <QImage>
#include <vector>
#include <tuple>
#include <imebra/imebra.h>
using namespace std;
using namespace imebra;

#define SS2QS(STR) (QString::fromStdString(STR))

class DicomUtils {
public:

    static QImage fromDicomFile(const QString &fileName);

    static vector<tuple<QString, QString>> getTags(const QString &fileName);
};

#endif //OPENGL_DICOMUTILS_H
