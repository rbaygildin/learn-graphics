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

Pyramid *TetrahedronInput::getPyramid() const {
    Point3D v1(ui->x1Inp->text().toDouble(), ui->y1Inp->text().toDouble(), ui->z1Inp->text().toDouble());
    Point3D v2(ui->x2Inp->text().toDouble(), ui->y2Inp->text().toDouble(), ui->z2Inp->text().toDouble());
    Point3D v3(ui->x3Inp->text().toDouble(), ui->y3Inp->text().toDouble(), ui->z3Inp->text().toDouble());
    Point3D v4(ui->x4Inp->text().toDouble(), ui->y4Inp->text().toDouble(), ui->z4Inp->text().toDouble());
    return new Pyramid(v1, v2, v3, v4);
}
