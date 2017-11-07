#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PI 3.1459


double sliderToRotate(int tick) {
    return (75.0 - tick) / 75.0 * 3.1459;
}

double sliderToScale(int tick) {
    return (tick + 1.0) / 20.0;
}

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    fig = MainWindow::Fig::CUBE;
    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);
    this->scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    createActions();
    createContextMenu();
}

void MainWindow::createActions() {
    //About
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutMenuItemClicked()));

    //Context menu
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->graphicsView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequested(QPoint)));

    //Rotation
    connect(ui->xRotateInput, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
    connect(ui->yRotateInput, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
    connect(ui->zRotateInput, SIGNAL(valueChanged(int)), this, SLOT(redraw()));

    //Remove lines
    connect(ui->removeLinesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(redraw()));

    //Scale
    connect(ui->xScaleInput, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
    connect(ui->yScaleInput, SIGNAL(valueChanged(int)), this, SLOT(redraw()));
    connect(ui->zScaleInput, SIGNAL(valueChanged(int)), this, SLOT(redraw()));

    //Move
    connect(ui->dxInput, SIGNAL(editingFinished()), this, SLOT(redraw()));
    connect(ui->dyInput, SIGNAL(editingFinished()), this, SLOT(redraw()));
    connect(ui->dzInput, SIGNAL(editingFinished()), this, SLOT(redraw()));
}

void MainWindow::createContextMenu() {

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

void MainWindow::contextMenuRequested(QPoint pos) {
    auto *menu = new QMenu(this);
    QAction *drawCubeAction = new QAction("Add cube", this);
    QAction *drawPyramidAction = new QAction("Add pyramid", this);
    QAction *drawOctahedronAction = new QAction("Add octahedron", this);
    QAction *drawIcosahedronAction = new QAction("Add icosahedron", this);
    QAction *drawAction = new QAction("Redraw", this);
    QAction *clearAction = new QAction("Clear", this);

    //Connect
    connect(drawCubeAction, SIGNAL(triggered()), this, SLOT(setCube()));
    connect(drawPyramidAction, SIGNAL(triggered(bool)), this, SLOT(setPyramid()));
    connect(drawOctahedronAction, SIGNAL(triggered(bool)), this, SLOT(setOctahedron()));
    connect(drawIcosahedronAction, SIGNAL(triggered(bool)), this, SLOT(setIcosahedron()));
    connect(drawAction, SIGNAL(triggered(bool)), this, SLOT(redraw()));
    connect(clearAction, SIGNAL(triggered(bool)), this, SLOT(clear()));

    //Add items
    menu->addAction(drawCubeAction);
    menu->addAction(drawPyramidAction);
    menu->addAction(drawOctahedronAction);
    menu->addAction(drawIcosahedronAction);
    menu->addAction(drawAction);
    menu->popup(ui->graphicsView->viewport()->mapToGlobal(pos));
}

void MainWindow::redraw() {
    drawAxes();
    switch (fig) {
        case CUBE:
            drawCube();
            break;
        case PYRAMID:
            drawPyramid();
            break;
        case OCT:
            drawOctahedron();
            break;
        case ICOS:
            drawIcosahedron();
            break;
    }
}

void MainWindow::drawCube() {
    double r = ui->rInput->text().toDouble();
    auto cube = new Cube(r, this->scene);
    cube
            ->rotate(
                    sliderToRotate(ui->xRotateInput->value()),
                    sliderToRotate(ui->yRotateInput->value()),
                    sliderToRotate(ui->zRotateInput->value())
            )
            ->scale(
                    sliderToScale(ui->xScaleInput->value()),
                    sliderToScale(ui->yScaleInput->value()),
                    sliderToScale(ui->zScaleInput->value())
            )
            ->translate(
                    ui->dxInput->text().toDouble(),
                    ui->dyInput->text().toDouble(),
                    ui->dzInput->text().toDouble()
            )
            ->removeHiddenLines(ui->removeLinesCheckBox->isChecked())
            ->parProject()
            ->paint();
    delete cube;
}

void MainWindow::drawPyramid() {
    double r = ui->rInput->text().toDouble();
    auto pyramid = new Pyramid(r, this->scene);
    pyramid
            ->rotate(
                    sliderToRotate(ui->xRotateInput->value()),
                    sliderToRotate(ui->yRotateInput->value()),
                    sliderToRotate(ui->zRotateInput->value())
            )
            ->scale(
                    sliderToScale(ui->xScaleInput->value()),
                    sliderToScale(ui->yScaleInput->value()),
                    sliderToScale(ui->zScaleInput->value())
            )
            ->translate(
                    ui->dxInput->text().toDouble(),
                    ui->dyInput->text().toDouble(),
                    ui->dzInput->text().toDouble()
            )
            ->removeHiddenLines(ui->removeLinesCheckBox->isChecked())
            ->parProject()
            ->paint();
    delete pyramid;
}

void MainWindow::drawOctahedron() {
    double r = ui->rInput->text().toDouble();
    auto octahedron = new Octahedron(r, this->scene);
    octahedron
            ->rotate(
                    sliderToRotate(ui->xRotateInput->value()),
                    sliderToRotate(ui->yRotateInput->value()),
                    sliderToRotate(ui->zRotateInput->value())
            )
            ->scale(
                    sliderToScale(ui->xScaleInput->value()),
                    sliderToScale(ui->yScaleInput->value()),
                    sliderToScale(ui->zScaleInput->value())
            )
            ->translate(
                    ui->dxInput->text().toDouble(),
                    ui->dyInput->text().toDouble(),
                    ui->dzInput->text().toDouble()
            )
            ->removeHiddenLines(ui->removeLinesCheckBox->isChecked())
            ->parProject()
            ->paint();
    delete octahedron;
}

void MainWindow::drawIcosahedron() {
    double r = ui->rInput->text().toDouble();
    auto icosahedron = new Icosahedron(r, this->scene);
    icosahedron
            ->rotate(
                    sliderToRotate(ui->xRotateInput->value()),
                    sliderToRotate(ui->yRotateInput->value()),
                    sliderToRotate(ui->zRotateInput->value())
            )
            ->scale(
                    sliderToScale(ui->xScaleInput->value()),
                    sliderToScale(ui->yScaleInput->value()),
                    sliderToScale(ui->zScaleInput->value())
            )
            ->translate(
                    ui->dxInput->text().toDouble(),
                    ui->dyInput->text().toDouble(),
                    ui->dzInput->text().toDouble()
            )
            ->removeHiddenLines(ui->removeLinesCheckBox->isChecked())
            ->parProject()
            ->paint();
    delete icosahedron;
}

void MainWindow::drawAxes() {
    QPen pen(Qt::blue);
    this->scene->clear();
    this->scene->addLine(0, ui->graphicsView->height() / 2, ui->graphicsView->width(), ui->graphicsView->height() / 2,
                         pen);
    this->scene->addLine(ui->graphicsView->width() / 2, 0, ui->graphicsView->width() / 2, ui->graphicsView->height(),
                         pen);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setCube() {
    fig = Fig::CUBE;
}

void MainWindow::setPyramid() {
    fig = Fig::PYRAMID;
}

void MainWindow::setOctahedron() {
    fig = Fig::OCT;
}

void MainWindow::setIcosahedron() {
    fig = Fig::ICOS;
}

void MainWindow::clear() {

}
