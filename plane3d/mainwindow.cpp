#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Scene
    this->scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    createActions();
}

void MainWindow::createActions() {
    //About
    connect(ui->aboutAction, SIGNAL(triggered(bool)), this, SLOT(aboutMenuItemClicked()));

    //Context menu
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    //Context menu
    connect(ui->graphicsView,
            SIGNAL(customContextMenuRequested(
                           const QPoint &)),
            this,
            SLOT(showMenu(
                         const QPoint &)));

    //Graphics View
    connect(ui->graphicsView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showMenu(QPoint)));

    //Rotate
    connect(ui->rotateXInp, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
    connect(ui->rotateYInp, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
    connect(ui->rotateZInp, SIGNAL(valueChanged(int)), this, SLOT(redraw()));

    //Remove hidden lines
    connect(ui->removeHiddenLinesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(redraw()));

    //Scale
    connect(ui->scaleXInp, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
    connect(ui->scaleYInp, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
    connect(ui->scaleZInp, SIGNAL(valueChanged(int)), this, SLOT(redraw()));

    //Translate
    connect(ui->dxInp, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
    connect(ui->dyInp, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
    connect(ui->dzInp, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
}

void MainWindow::aboutMenuItemClicked() {
    QMessageBox msgBox;
    msgBox.setText(
            "<p>Разработка: Ярных Роман, студент БПИ141, 2017</p>"
                    "<p>1. Реализация проецирования 3D фигур на плоскость</p>"
                    "<p>2. Базовые преобразования (вращение, масштабирование, перемещение)</p>"
                    "<p>3. Удаление невидимых граней и линий</p>"
    );
    msgBox.exec();
}

void MainWindow::showMenu(QPoint pos) {
    auto *menu = new QMenu(this);
    //Add figure
    QAction *drawCubeAction = new QAction("Добавить куб", this);
    QAction *drawPyramidAction = new QAction("Добавить пирамиду", this);
    QAction *drawOctahedronAction = new QAction("Добавить октаэдр", this);
    QAction *drawIcosahedronAction = new QAction("Добавить икосаэдр", this);

    //Redraw
    QAction *drawAction = new QAction("Перерисовать", this);

    //Clear
    QAction *clearAction = new QAction("Очистить", this);

    //Connect
    connect(drawCubeAction, SIGNAL(triggered()), this, SLOT(addCube()));
    connect(drawPyramidAction, SIGNAL(triggered(bool)), this, SLOT(addPyramid()));
    connect(drawOctahedronAction, SIGNAL(triggered(bool)), this, SLOT(addOctahedron()));
    connect(drawIcosahedronAction, SIGNAL(triggered(bool)), this, SLOT(addIcosahedron()));
    connect(drawAction, SIGNAL(triggered(bool)), this, SLOT(redraw()));
    connect(clearAction, SIGNAL(triggered(bool)), this, SLOT(clear()));

    //Add action
    menu->addAction(drawCubeAction);
    menu->addAction(drawPyramidAction);
    menu->addAction(drawOctahedronAction);
    menu->addAction(drawIcosahedronAction);
    menu->addAction(drawAction);
    menu->addAction(clearAction);

    //Init menu
    menu->popup(ui->graphicsView->viewport()->mapToGlobal(pos));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::redraw() {
    for(auto &figure : figures)
        figure->paint();
}

void MainWindow::clear() {
    for (auto &figure : figures)
        delete figure;
    figures.clear();
    scene->clear();
}

void MainWindow::addCube() {
    auto fig = new Cube(ui->edgeInp->text().toDouble(), scene);
    figures.emplace_back(fig);
    redraw();
}

void MainWindow::addPyramid() {
    auto fig = new Pyramid(ui->edgeInp->text().toDouble(), scene);
    figures.emplace_back(fig);
    redraw();
}

void MainWindow::addOctahedron() {
    auto fig = new Octahedron(ui->edgeInp->text().toDouble(), scene);
    figures.emplace_back(fig);
    redraw();
}

void MainWindow::addIcosahedron() {
    auto fig = new Icosahedron(ui->edgeInp->text().toDouble(), scene);
    figures.emplace_back(fig);
    redraw();
}
