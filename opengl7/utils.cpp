#include "utils.h"

QString readFile(const QString &fileName) {
    QFile inputFile(fileName);
    QString res = "";
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            res += line + "\n";
        }
        inputFile.close();
    }
    return res;
}


