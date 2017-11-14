#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figures/polygons/cube.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(ui->graphicsView);
    auto torus = new Cube();
    torus->setEdge(50);
    ui->graphicsView->setScene(scene);
    connect(torus, SIGNAL(signal1()), this, SLOT(hello()));
    scene->addItem(torus);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hello(){
    QMessageBox::information(this,
                                 "Зафиксировано нажатие",
                                 "Вы нажали на точку!!!"
                                 "\n"
                                 "\n"
                                 "\n      С Уважением, Ваш КЭП!!!");
}
