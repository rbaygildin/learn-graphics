#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PI 3.1459


double sliderToRotate(int tick) {
    return (75.0 - tick) / 75.0 * 3.1459;
}

double sliderToScale(int tick) {
    return (tick + 0.001) / 30.0;
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
    connect(ui->xRotateInput, SIGNAL(valueChanged(int)), this, SLOT(rotate()));
    connect(ui->yRotateInput, SIGNAL(valueChanged(int)), this, SLOT(rotate()));
    connect(ui->zRotateInput, SIGNAL(valueChanged(int)), this, SLOT(rotate()));

    //Remove lines
    connect(ui->removeLinesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(redraw()));

    //Scale
    connect(ui->xScaleInput, SIGNAL(valueChanged(int)), this, SLOT(scale()));
    connect(ui->yScaleInput, SIGNAL(valueChanged(int)), this, SLOT(scale()));
    connect(ui->zScaleInput, SIGNAL(valueChanged(int)), this, SLOT(scale()));

    //Move
    connect(ui->dxInput, SIGNAL(editingFinished()), this, SLOT(move()));
    connect(ui->dyInput, SIGNAL(editingFinished()), this, SLOT(move()));
    connect(ui->dzInput, SIGNAL(editingFinished()), this, SLOT(move()));

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
        addCube();
    });
    connect(drawPyramidAction, &QAction::triggered, this, [this, pos]() {
        addPyramid();
    });
    connect(drawOctahedronAction, &QAction::triggered, this, [this, pos]() {
        addOctahedron();
    });
    connect(drawIcosahedronAction, &QAction::triggered, this, [this, pos]() {
        addIcosahedron();
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

void MainWindow::addCube() {
    double r = ui->rInput->text().toDouble();
    auto cube = new Cube(r, this->scene);
    QListWidgetItem *item = new QListWidgetItem("Cube");
    item->setData(Qt::UserRole, qVariantFromValue((void *) cube));
    ui->listWidget->addItem(item);
    figures.emplace_back(cube);
    redraw();
}

void MainWindow::addPyramid() {
    double r = ui->rInput->text().toDouble();
    auto cube = new Pyramid(r, this->scene);
    QListWidgetItem *item = new QListWidgetItem("Pyramid");
    item->setData(Qt::UserRole, qVariantFromValue((void *) cube));
    ui->listWidget->addItem(item);
    figures.emplace_back(cube);
    redraw();
}

void MainWindow::addOctahedron() {
    double r = ui->rInput->text().toDouble();
    auto cube = new Octahedron(r, this->scene);
    QListWidgetItem *item = new QListWidgetItem("Octahedron");
    item->setData(Qt::UserRole, qVariantFromValue((void *) cube));
    ui->listWidget->addItem(item);
    figures.emplace_back(cube);
    redraw();
}

void MainWindow::addIcosahedron() {
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
        selectedFigure->translate(
                ui->dxInput->text().toDouble(),
                ui->dyInput->text().toDouble(),
                ui->dzInput->text().toDouble()
        );
        redraw();
    }
}
