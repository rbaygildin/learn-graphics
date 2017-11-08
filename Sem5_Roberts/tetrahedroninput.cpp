#include "tetrahedroninput.h"
#include "ui_tetrahedroninput.h"

TetrahedronInput::TetrahedronInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TetrahedronInput)
{
    ui->setupUi(this);
    connect(ui->addBtn, SIGNAL(clicked(bool)), this, SLOT(add()));
}

void TetrahedronInput::add() {
    this->close();
}

TetrahedronInput::~TetrahedronInput()
{
    delete ui;
}

PointF3d TetrahedronInput::v1() {
    return PointF3d(ui->x1Inp->text().toDouble(), ui->y1Inp->text().toDouble(), ui->z1Inp->text().toDouble());
}

PointF3d TetrahedronInput::v2() {
    return PointF3d(ui->x2Inp->text().toDouble(), ui->y2Inp->text().toDouble(), ui->z2Inp->text().toDouble());
}

PointF3d TetrahedronInput::v3() {
    return PointF3d(ui->x3Inp->text().toDouble(), ui->y3Inp->text().toDouble(), ui->z3Inp->text().toDouble());
}

PointF3d TetrahedronInput::v4() {
    return PointF3d(ui->x4Inp->text().toDouble(), ui->y4Inp->text().toDouble(), ui->z4Inp->text().toDouble());
}
