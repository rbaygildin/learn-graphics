#ifndef TETRAHEDRONINPUT_H
#define TETRAHEDRONINPUT_H

#include <QDialog>
#include "figures/polygons/pyramid.h"

namespace Ui {
class TetrahedronInput;
}

class TetrahedronInput : public QDialog
{
    Q_OBJECT

public:
    explicit TetrahedronInput(QWidget *parent = 0);
    Pyramid* getPyramid() const;
    ~TetrahedronInput() override;

public slots:
    void add();

private:
    Ui::TetrahedronInput *ui;
};

#endif // TETRAHEDRONINPUT_H
