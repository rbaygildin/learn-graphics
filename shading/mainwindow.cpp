#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "figures/polygons/cube.h"

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
    for (auto &figure : figures) {
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
        } else if (figureJson["type"] == "OCTAHEDRON") {
            figure = new Octahedron(figureJson["edge"].toDouble());
        } else if (figureJson["type"] == "ICOSAHEDRON") {
            figure = new Icosahedron(figureJson["edge"].toDouble());
        } else
            continue;
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
    );
    msgBox.exec();
}

void MainWindow::showGraphicsViewMenu(QPoint pos) {
    auto *menu = new QMenu(this);
    QAction *drawCubeAction = new QAction("Добавить куб", this);
    QAction *drawPyramidAction = new QAction("Добавить пирамиду", this);
    QAction *drawOctahedronAction = new QAction("Добавить октаэдр", this);
    QAction *drawIcosahedronAction = new QAction("Добавить икосаэдр", this);
    QAction *drawTetrahedronAction = new QAction("Add tetrahedron", this);
    QAction *drawAction = new QAction("Перерисовать", this);
    QAction *clearAction = new QAction("Очистить", this);
    QAction *restoreAction = new QAction("Восстановить", this);

    //Connect
    connect(drawCubeAction, &QAction::triggered, this, [this, pos]() {
        addCube(QPoint());
    });
    connect(drawPyramidAction, &QAction::triggered, this, [this, pos]() {
        addRegularPyramid(QPoint());
    });
    connect(drawOctahedronAction, &QAction::triggered, this, [this, pos]() {
        addOctahedron(QPoint());
    });
    connect(drawIcosahedronAction, &QAction::triggered, this, [this, pos]() {
        addIcosahedron(QPoint());
    });
//    connect(drawTetrahedronAction, &QAction::triggered, this, [this, pos]() {
//        addTetrahedron(pos);
//    });

    connect(drawAction, SIGNAL(triggered(bool)), this, SLOT(redraw()));
    connect(clearAction, SIGNAL(triggered(bool)), this, SLOT(clear()));
    connect(restoreAction, SIGNAL(triggered(bool)), this, SLOT(restore()));

    //Add items
    menu->addAction(drawCubeAction);
    menu->addAction(drawPyramidAction);
    menu->addAction(drawOctahedronAction);
    menu->addAction(drawIcosahedronAction);
    menu->addAction(drawTetrahedronAction);
    menu->addAction(drawAction);
    menu->addAction(clearAction);
    menu->addAction(restoreAction);
    menu->popup(ui->graphicsView->viewport()->mapToGlobal(pos));
}

void MainWindow::addCube(QPoint pos) {
    double r = ui->edgeInp->text().toDouble();
    auto figure = new Cube(r == 0.0 ? 50 : r);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addOctahedron(QPoint pos) {
    double r = ui->edgeInp->text().toDouble();
    auto figure = new Octahedron(r == 0.0 ? 50 : r);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addRegularPyramid(QPoint pos) {
    double r = ui->edgeInp->text().toDouble();
    auto figure = new RegularPyramid(r == 0.0 ? 50 : r);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addIcosahedron(QPoint pos) {
    double r = ui->edgeInp->text().toDouble();
    auto figure = new Icosahedron(r == 0.0 ? 50 : r);
    scene->addItem(figure);
    redraw();
}

void MainWindow::addPyramid(QPoint pos) {

}

void MainWindow::clear() {
    for (auto &figure : figures)
        delete figure;
    figures.clear();
    scene->clear();
}

void MainWindow::redraw() {
    scene->update();
}

void MainWindow::restore() {

}

void MainWindow::rotateX() {
    for(auto &item : scene->items()){
        auto figure = dynamic_cast<Figure*>(item);
        if(item == nullptr)
            continue;
        figure->transform(Figure::RotateX, degree2radian(slider2degree(ui->rxInp->value())));
    }
    redraw();
}

void MainWindow::rotateY() {
    for(auto &item : scene->items()){
        auto figure = dynamic_cast<Figure*>(item);
        if(item == nullptr)
            continue;
        figure->transform(Figure::RotateY, degree2radian(slider2degree(ui->ryInp->value())));
    }
    redraw();
}

void MainWindow::rotateZ() {
    for(auto &item : scene->items()){
        auto figure = dynamic_cast<Figure*>(item);
        if(item == nullptr)
            continue;
        figure->transform(Figure::RotateZ, degree2radian(slider2degree(ui->rzInp->value())));
    }
    redraw();
}

void MainWindow::scaleX() {
    for(auto &item : scene->items()){
        auto figure = dynamic_cast<Figure*>(item);
        if(item == nullptr)
            continue;
        figure->transform(Figure::ScaleX, slider2scale(ui->sxInp->value()));
    }
    redraw();
}

void MainWindow::scaleY() {
    for(auto &item : scene->items()){
        auto figure = dynamic_cast<Figure*>(item);
        if(item == nullptr)
            continue;
        figure->transform(Figure::ScaleY, slider2scale(ui->syInp->value()));
    }
    redraw();
}

void MainWindow::scaleZ() {
    for(auto &item : scene->items()){
        auto figure = dynamic_cast<Figure*>(item);
        if(item == nullptr)
            continue;
        figure->transform(Figure::ScaleZ, slider2scale(ui->szInp->value()));
    }
    redraw();
}

void MainWindow::moveX() {
    for(auto &item : scene->items()){
        auto figure = dynamic_cast<Figure*>(item);
        if(item == nullptr)
            continue;
        figure->transform(Figure::TranslateX, ui->dxInp->value());
    }
    redraw();
}

void MainWindow::moveY() {
    for(auto &item : scene->items()){
        auto figure = dynamic_cast<Figure*>(item);
        if(item == nullptr)
            continue;
        figure->transform(Figure::TranslateY, ui->dyInp->value());
    }
    redraw();
}

void MainWindow::moveZ() {
    for(auto &item : scene->items()){
        auto figure = dynamic_cast<Figure*>(item);
        if(item == nullptr)
            continue;
        figure->transform(Figure::TranslateZ, ui->dzInp->value());
    }
    redraw();
}
