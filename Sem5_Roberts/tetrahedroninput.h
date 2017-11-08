#ifndef TETRAHEDRONINPUT_H
#define TETRAHEDRONINPUT_H

#include <QDialog>
#include "figures/pointf3d.h"

namespace Ui {
class TetrahedronInput;
}

class TetrahedronInput : public QDialog
{
    Q_OBJECT

public:
    explicit TetrahedronInput(QWidget *parent = 0);
    PointF3d v1();
    PointF3d v2();
    PointF3d v3();
    PointF3d v4();
    ~TetrahedronInput() override;

public slots:
    void add();

private:
    Ui::TetrahedronInput *ui;
};

#endif // TETRAHEDRONINPUT_H
