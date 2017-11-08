#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PI 3.1459


double sliderToRotate(int tick) {
    return (75.0 - tick) / 75.0 * 3.1459;
}

double sliderToScale(int tick) {
    return (tick * 1.0 + 1.0) / 50.0;
}

double d2r(double degrees) {
    return degrees * PI / 180.0;
}

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->menuBar->setNativeMenuBar(false);

    //Scene
    this->scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    //Disable scrolling
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->showFullScreen();

    //Create actions
    createActions();

    //Install event filter
    ui->graphicsView->installEventFilter(this);
}

void MainWindow::createActions() {
    //About
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(aboutMenuItemClicked()));

    //Context menu
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->graphicsView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequested(QPoint)));

    //Rotation
    //Rotate x
    connect(ui->xRotateInput, SIGNAL(valueChanged(int)), this, SLOT(rotateX()));
    //Rotate y
    connect(ui->yRotateInput, SIGNAL(valueChanged(int)), this, SLOT(rotateY()));
    //Rotate z
    connect(ui->zRotateInput, SIGNAL(valueChanged(int)), this, SLOT(rotateZ()));

    //Remove lines
    connect(ui->removeLinesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(redraw()));

    //Scale
    //Scale x
    connect(ui->xScaleInput, SIGNAL(valueChanged(int)), this, SLOT(scaleX()));
    //Scale y
    connect(ui->yScaleInput, SIGNAL(valueChanged(int)), this, SLOT(scaleY()));
    //Scale y
    connect(ui->zScaleInput, SIGNAL(valueChanged(int)), this, SLOT(scaleZ()));

    //Move
    //Move x
    connect(ui->dxInput, SIGNAL(editingFinished()), this, SLOT(moveX()));
    //Move y
    connect(ui->dyInput, SIGNAL(editingFinished()), this, SLOT(moveY()));
    //Move z
    connect(ui->dzInput, SIGNAL(editingFinished()), this, SLOT(moveZ()));

    //Select figure
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem * )), this, SLOT(selectFigure(QListWidgetItem * )));
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
    QAction *restoreAction = new QAction("Restore", this);

    //Connect
    connect(drawCubeAction, &QAction::triggered, this, [this, pos]() {
        addCube(pos);
    });
    connect(drawPyramidAction, &QAction::triggered, this, [this, pos]() {
        addPyramid(pos);
    });
    connect(drawOctahedronAction, &QAction::triggered, this, [this, pos]() {
        addOctahedron(pos);
    });
    connect(drawIcosahedronAction, &QAction::triggered, this, [this, pos]() {
        addIcosahedron(pos);
    });
    connect(drawAction, SIGNAL(triggered(bool)), this, SLOT(redraw()));
    connect(clearAction, SIGNAL(triggered(bool)), this, SLOT(clear()));
    connect(restoreAction, SIGNAL(triggered(bool)), this, SLOT(restore()));

    //Add items
    menu->addAction(drawCubeAction);
    menu->addAction(drawPyramidAction);
    menu->addAction(drawOctahedronAction);
    menu->addAction(drawIcosahedronAction);
    menu->addAction(drawAction);
    menu->addAction(clearAction);
    menu->addAction(restoreAction);
    menu->popup(ui->graphicsView->viewport()->mapToGlobal(pos));
}

void MainWindow::redraw() {
    drawAxes();
    for (auto &figure : figures) {
        figure->removeHiddenLines(ui->removeLinesCheckBox->isChecked())
                ->parProject()
                ->paint();
    }
}

void MainWindow::addCube(QPoint pos) {
    double r = ui->rInput->text().toDouble();
    auto cube = new Cube(r, this->scene);
    QListWidgetItem *item = new QListWidgetItem("Cube");
    item->setData(Qt::UserRole, qVariantFromValue((void *) cube));
    ui->listWidget->addItem(item);
    figures.emplace_back(cube);
    redraw();
}

void MainWindow::addPyramid(QPoint pos) {
    double r = ui->rInput->text().toDouble();
    auto cube = new Pyramid(r, this->scene);
    QListWidgetItem *item = new QListWidgetItem("Pyramid");
    item->setData(Qt::UserRole, qVariantFromValue((void *) cube));
    ui->listWidget->addItem(item);
    figures.emplace_back(cube);
    redraw();
}

void MainWindow::addOctahedron(QPoint pos) {
    double r = ui->rInput->text().toDouble();
    auto cube = new Octahedron(r, this->scene);
    QListWidgetItem *item = new QListWidgetItem("Octahedron");
    item->setData(Qt::UserRole, qVariantFromValue((void *) cube));
    ui->listWidget->addItem(item);
    figures.emplace_back(cube);
    redraw();
}

void MainWindow::addIcosahedron(QPoint pos) {
    double r = ui->rInput->text().toDouble();
    auto cube = new Icosahedron(r, this->scene);
    QListWidgetItem *item = new QListWidgetItem("Icosahedron");
    item->setData(Qt::UserRole, qVariantFromValue((void *) cube));
    ui->listWidget->addItem(item);
    figures.emplace_back(cube);
    redraw();
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
    for (auto &figure : figures)
        delete figure;
    delete ui;
}

void MainWindow::clear() {
    for (auto &figure : figures)
        delete figure;
    figures.clear();
    scene->clear();
    ui->listWidget->clear();
    selectedFigure = nullptr;
}


bool MainWindow::eventFilter(QObject *target, QEvent *event) {
    if (target == ui->graphicsView) {
//        if (event->type() == QEvent::Wheel) {
//            auto *wheelEvent = dynamic_cast<QWheelEvent *>(event);
//            scene->clear();
//            //Rotation y
//            if (wheelEvent->orientation() == Qt::Horizontal) {
//                for (auto &figure : figures) {
//                    figure->restore();
//                    figure->rotate(0, d2r(wheelEvent->delta() / 120.0), 0)
//                            ->parProject()
//                            ->paint();
//                }
//            }//Rotation x or z
//            else if (wheelEvent->orientation() == Qt::Vertical) {
//                for (auto &figure : figures) {
//                    figure->restore();
//                    if (ui->checkBox->isChecked()) {
//                        figure->rotate(0, 0, d2r(wheelEvent->delta() / 120.0))
//                                ->parProject()
//                                ->paint();
//                    } else {
//                        figure->rotate(d2r(wheelEvent->delta() / 120.0), 0, 0)
//                                ->parProject()
//                                ->paint();
//                    }
//                }
//            }
//            return true;
//        }
//    }
    }
    return QMainWindow::eventFilter(target, event);
}

void MainWindow::restore() {
    for (auto &figure : figures)
        figure->restore();
    redraw();
}

void MainWindow::selectFigure(QListWidgetItem *item) {
    if (selectedFigure != nullptr)
        selectedFigure->setSelected(false);
    selectedFigure = (IFigure *) item->data(Qt::UserRole).value<void *>();
    selectedFigure->setSelected(true);
}

void MainWindow::scale() {
    if (selectedFigure != nullptr) {
        selectedFigure->restore();
        selectedFigure->scale(
                sliderToScale(ui->xScaleInput->value()),
                sliderToScale(ui->yScaleInput->value()),
                sliderToScale(ui->zScaleInput->value())
        );
        redraw();
    }
}

void MainWindow::rotate() {
    if (selectedFigure != nullptr) {
        selectedFigure->restore();
        selectedFigure->rotate(
                sliderToRotate(ui->xRotateInput->value()),
                sliderToRotate(ui->yRotateInput->value()),
                sliderToRotate(ui->zRotateInput->value())
        );
        redraw();
    }
}

void MainWindow::move() {
    if (selectedFigure != nullptr) {
        selectedFigure->restore();
        selectedFigure->translate(
                ui->dxInput->text().toDouble(),
                ui->dyInput->text().toDouble(),
                ui->dzInput->text().toDouble()
        );
        redraw();
    }
}

void MainWindow::rotateX() {
    if (selectedFigure != nullptr) {
        selectedFigure->rotate(
                sliderToRotate(ui->xRotateInput->value()),
                0,
                0
        );
        redraw();
    }
}

void MainWindow::rotateY() {
    if (selectedFigure != nullptr) {
        selectedFigure->rotate(
                0,
                sliderToRotate(ui->yRotateInput->value()),
                0
        );
        redraw();
    }
}

void MainWindow::rotateZ() {
    if (selectedFigure != nullptr) {
        selectedFigure->rotate(
                0,
                0,
                sliderToRotate(ui->zRotateInput->value())
        );
        redraw();
    }
}

void MainWindow::scaleX() {
    if (selectedFigure != nullptr) {
        selectedFigure->restore();
        selectedFigure->scale(
                sliderToScale(ui->xScaleInput->value()),
                1,
                1
        );
        redraw();
    }
}

void MainWindow::scaleY() {
    if (selectedFigure != nullptr) {
        selectedFigure->restore();
        selectedFigure->scale(
                1,
                sliderToScale(ui->yScaleInput->value()),
                1
        );
        redraw();
    }
}

void MainWindow::scaleZ() {
    if (selectedFigure != nullptr) {
        selectedFigure->restore();
        selectedFigure->scale(
                1,
                1,
                sliderToScale(ui->zScaleInput->value())
        );
        redraw();
    }
}

void MainWindow::moveX() {
    if (selectedFigure != nullptr) {
        selectedFigure->translate(
                ui->dxInput->text().toDouble(),
                0,
                0
        );
        redraw();
    }
}

void MainWindow::moveY() {
    if (selectedFigure != nullptr) {
        selectedFigure->translate(
                0,
                ui->dyInput->text().toDouble(),
                0
        );
        redraw();
    }
}

void MainWindow::moveZ() {
    if (selectedFigure != nullptr) {
        selectedFigure->translate(
                0,
                0,
                ui->dzInput->text().toDouble()
        );
        redraw();
    }
}
