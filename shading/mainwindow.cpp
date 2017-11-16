#include <QColorDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figures/polygons/cube.h"
#include "figures/nonconvex/sphere.h"
#include "figures/nonconvex/klein_bottle.h"
#include "figures/nonconvex/spiral.h"
#include "tetrahedroninput.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->menuBar->setNativeMenuBar(false);

    //Menu actions
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(about()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(open()));

    //Context menu
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->graphicsView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showGraphicsViewMenu(QPoint)));

    //Rotation
    //Rotate x
    connect(ui->rxInp, SIGNAL(valueChanged(int)), this, SLOT(rotateX()));
    //Rotate y
    connect(ui->ryInp, SIGNAL(valueChanged(int)), this, SLOT(rotateY()));
    //Rotate z
    connect(ui->rzInp, SIGNAL(valueChanged(int)), this, SLOT(rotateZ()));

    //Scale
    //Scale x
    connect(ui->sxInp, SIGNAL(valueChanged(int)), this, SLOT(scaleX()));
    //Scale y
    connect(ui->syInp, SIGNAL(valueChanged(int)), this, SLOT(scaleY()));
    //Scale y
    connect(ui->szInp, SIGNAL(valueChanged(int)), this, SLOT(scaleZ()));

    //Move
    //Move x
    connect(ui->dxInp, SIGNAL(valueChanged(int)), this, SLOT(moveX()));
    //Move y
    connect(ui->dyInp, SIGNAL(valueChanged(int)), this, SLOT(moveY()));
    //Move z
    connect(ui->dzInp, SIGNAL(valueChanged(int)), this, SLOT(moveZ()));

    //Choose color
    connect(ui->chooseColorBtn, SIGNAL(clicked()), this, SLOT(chooseColor()));
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Сохранить фигуру"), "",
                                                    tr("Фигуры (*.json);;Все файлы (*)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, QString("Невозможно сохранить фигуры"), file.errorString());
    }
    QJsonObject obj;
    QJsonArray array;
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        array.append(figure->toJson());
    }
    obj.insert("figures", array);
    QJsonDocument doc(obj);
    file.write(doc.toJson());
    file.close();
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Открыть фигуры"), "",
                                                    tr("Фигуры (*.json);;Все файлы (*)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, QString("Не могу открыть файл"), file.errorString());
    }
    QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
    file.close();
    clear();
    for (auto &&item : obj["figures"].toArray()) {
        QJsonObject figureJson = item.toObject();
        Figure *figure;
        if (figureJson["type"] == "CUBE") {
            figure = new Cube(figureJson["edge"].toDouble());
        } else if (figureJson["type"] == "REGULAR_PYRAMID") {
            figure = new RegularPyramid(figureJson["edge"].toDouble());
        } else if (figureJson["type"] == "PYRAMID") {
            QJsonArray vArray = figureJson["vertex"].toArray();
            std::vector<Point3D> vertex;
            for (int i = 0; i < 4; i++) {
                vertex.emplace_back(
                        Point3D(
                                vArray.at(i * 4 + 0).toDouble(),
                                vArray.at(i * 4 + 1).toDouble(),
                                vArray.at(i * 4 + 2).toDouble()
                        )
                );
            }
            figure = new Pyramid(vertex[0], vertex[1], vertex[2], vertex[3]);
        } else if (figureJson["type"] == "OCTAHEDRON") {
            figure = new Octahedron(figureJson["edge"].toDouble());
        } else if (figureJson["type"] == "ICOSAHEDRON") {
            figure = new Icosahedron(figureJson["edge"].toDouble());
        } else if (figureJson["type"] == "TORUS") {
            figure = new Torus(figureJson["R"].toDouble(), figureJson["r"].toDouble());
        } else if (figureJson["type"] == "SPHERE") {
            figure = new Sphere(figureJson["R"].toDouble());
        } else if (figureJson["type"] == "SPIRAL") {
            figure = new Spiral(figureJson["R"].toDouble(), figureJson["r"].toDouble());
        } else
            continue;
        initItem(figure);
        QJsonArray trArray = figureJson["transformations"].toArray();
        for (int i = 0; i < trArray.size(); i++)
            figure->transform(i, trArray.at(i).toDouble());
        scene->addItem(figure);
    }

    redraw();

}

void MainWindow::about() {
    QMessageBox msgBox;
    msgBox.setText(
            "<p>Разработка: Ярных Роман, студент БПИ141, 2017</p>"
                    "<p>1. Реализация проецирования 3D фигур на плоскость</p>"
                    "<p>2. Базовые преобразования (вращение, масштабирование, перемещение)</p>"
                    "<p>3. Удаление невидимых граней и линий</p>"
                    "<p>4. Рисование сферы и тора</p>"
                    "<p>5. Освещение</p>"
    );
    msgBox.exec();
}

void MainWindow::showGraphicsViewMenu(QPoint pos) {
    auto *menu = new QMenu(this);
    QAction *drawCubeAction = new QAction("Добавить куб", this);
    QAction *drawRegularPyramidAction = new QAction("Добавить правильную пирамиду", this);
    QAction *drawPyramidAction = new QAction("Добавить тертраэдр", this);
    QAction *drawOctahedronAction = new QAction("Добавить октаэдр", this);
    QAction *drawIcosahedronAction = new QAction("Добавить икосаэдр", this);
    QAction *drawSphereAction = new QAction("Добавить сферу", this);
    QAction *drawTorusAction = new QAction("Добавить тор", this);
    QAction *drawSpiralAction = new QAction("Добавить спираль", this);
    QAction *drawKleinBottleAction = new QAction("Добавить бутылку Клейна", this);
    QAction *drawAction = new QAction("Перерисовать", this);
    QAction *clearAction = new QAction("Очистить", this);
    QAction *restoreAction = new QAction("Восстановить", this);
    QAction *backgroundAction = new QAction("Цвет фона", this);

    //Connect
    connect(drawCubeAction, &QAction::triggered, this, [this, pos]() {
        addCube(pos);
    });
    connect(drawRegularPyramidAction, &QAction::triggered, this, [this, pos]() {
        addRegularPyramid(pos);
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
    connect(drawTorusAction, &QAction::triggered, this, [this, pos]() {
        addTorus(pos);
    });
    connect(drawSphereAction, &QAction::triggered, this, [this, pos]() {
        addSphere(pos);
    });
    connect(drawSpiralAction, &QAction::triggered, this, [this, pos]() {
        addSpiral(pos);
    });
    connect(drawKleinBottleAction, &QAction::triggered, this, [this, pos]() {
        addKleinBottle(pos);
    });

    connect(drawAction, SIGNAL(triggered(bool)), this, SLOT(redraw()));
    connect(clearAction, SIGNAL(triggered(bool)), this, SLOT(clear()));
    connect(restoreAction, SIGNAL(triggered(bool)), this, SLOT(restore()));
    connect(backgroundAction, SIGNAL(triggered(bool)), this, SLOT(setBackground()));

    //Add items
    menu->addSection("Фигуры");
    menu->addAction(drawCubeAction);
    menu->addAction(drawRegularPyramidAction);
    menu->addAction(drawPyramidAction);
    menu->addAction(drawOctahedronAction);
    menu->addAction(drawIcosahedronAction);
    menu->addAction(drawTorusAction);
    menu->addAction(drawSphereAction);
    menu->addAction(drawSpiralAction);
    menu->addAction(drawKleinBottleAction);
    menu->addSection("Операции");
    menu->addAction(drawAction);
    menu->addAction(clearAction);
    menu->addAction(restoreAction);
    menu->addAction(backgroundAction);
    menu->popup(ui->graphicsView->viewport()->mapToGlobal(pos));
}

void MainWindow::addCube(QPoint pos) {
    double r = ui->edgeInp->text().toDouble();
    auto figure = new Cube(r == 0.0 ? 50 : r);
    initItem(figure);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addOctahedron(QPoint pos) {
    double r = ui->edgeInp->text().toDouble();
    auto figure = new Octahedron(r == 0.0 ? 50 : r);
    initItem(figure);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addRegularPyramid(QPoint pos) {
    double r = ui->edgeInp->text().toDouble();
    auto figure = new RegularPyramid(r == 0.0 ? 50 : r);
    initItem(figure);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addIcosahedron(QPoint pos) {
    double r = ui->edgeInp->text().toDouble();
    auto figure = new Icosahedron(r == 0.0 ? 50 : r);
    initItem(figure);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addTorus(QPoint pos) {
    auto figure = new Torus();
    initItem(figure);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addSphere(QPoint point) {
    auto figure = new Sphere();
    initItem(figure);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addSpiral(QPoint point) {
    auto figure = new Spiral();
    initItem(figure);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addKleinBottle(QPoint point) {
    auto figure = new KleinBottle();
    initItem(figure);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addPyramid(QPoint pos) {
    auto *dialog = new TetrahedronInput(this);
    dialog->exec();
    auto figure = dialog->getPyramid();
    initItem(figure);
    scene->addItem(figure);
    redraw();
}

void MainWindow::clear() {
    scene->clear();
    redraw();
}

void MainWindow::redraw() {
    scene->update();
}

void MainWindow::restore() {
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        figure->identityTransform();
    }
    redraw();
}

void MainWindow::rotateX() {
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        figure->transform(Figure::RotateX, degree2radian(slider2degree(ui->rxInp->value())));
    }
    redraw();
}

void MainWindow::rotateY() {
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        figure->transform(Figure::RotateY, degree2radian(slider2degree(ui->ryInp->value())));
    }
    redraw();
}

void MainWindow::rotateZ() {
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        figure->transform(Figure::RotateZ, degree2radian(slider2degree(ui->rzInp->value())));
    }
    redraw();
}

void MainWindow::scaleX() {
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        figure->transform(Figure::ScaleX, slider2scale(ui->sxInp->value()));
    }
    redraw();
}

void MainWindow::scaleY() {
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        figure->transform(Figure::ScaleY, slider2scale(ui->syInp->value()));
    }
    redraw();
}

void MainWindow::scaleZ() {
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        figure->transform(Figure::ScaleZ, slider2scale(ui->szInp->value()));
    }
    redraw();
}

void MainWindow::moveX() {
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        figure->transform(Figure::TranslateX, ui->dxInp->value());
    }
    redraw();
}

void MainWindow::moveY() {
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        figure->transform(Figure::TranslateY, ui->dyInp->value());
    }
    redraw();
}

void MainWindow::moveZ() {
    for (auto &item : scene->items()) {
        auto figure = dynamic_cast<Figure *>(item);
        if (item == nullptr)
            continue;
        figure->transform(Figure::TranslateZ, ui->dzInp->value());
    }
    redraw();
}

void MainWindow::chooseColor() {
    color = QColorDialog::getColor(Qt::red, this);
    QPalette pal;
    pal.setColor(QPalette::Background, color);
    ui->colorLabel->setPalette(pal);
}

void MainWindow::initItem(Figure *item) {
    if(ui->meshRadio->isChecked())
        item->setMeshMode();
    else
        item->setWithLightingMode();
    item->color = color;
    item->ia = ui->iaInp->value() / 5.0 + 1;
    item->id = ui->idInp->value() / 5.0 + 1;
    item->n = ui->nInp->value() / 10 + 1;
    connect(ui->iaInp, SIGNAL(valueChanged(int)), item, SLOT(changeAmbient(int)));
    connect(ui->idInp, SIGNAL(valueChanged(int)), item, SLOT(changeDiffuse(int)));
    connect(ui->meshRadio, SIGNAL(toggled(bool)), item, SLOT(setMeshMode()));
    connect(ui->lightingRadio, SIGNAL(toggled(bool)), item, SLOT(setWithLightingMode()));
    connect(ui->lampXInp, SIGNAL(valueChanged(int)), item, SLOT(changeLampX(int)));
    connect(ui->lampYInp, SIGNAL(valueChanged(int)), item, SLOT(changeLampY(int)));
    connect(ui->lampZInp, SIGNAL(valueChanged(int)), item, SLOT(changeLampZ(int)));
    connect(ui->kdInp, SIGNAL(valueChanged(int)), item, SLOT(changeKd(int)));
    connect(ui->kaInp, SIGNAL(valueChanged(int)), item, SLOT(changeKa(int)));
    connect(ui->ksInp, SIGNAL(valueChanged(int)), item, SLOT(changeKs(int)));
    connect(ui->nInp, SIGNAL(valueChanged(int)), item, SLOT(changeKa(int)));
}

void MainWindow::setBackground() {
    QColor col = QColorDialog::getColor(Qt::red, this);
    scene->setBackgroundBrush(QBrush(col));
}


