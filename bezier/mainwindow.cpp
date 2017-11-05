#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);
    ui->graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
    //Scene
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    //Action events
    connect(ui->aboutProgramAction, SIGNAL(triggered(bool)), this, SLOT(aboutActionClicked()));
    connect(ui->openAction, SIGNAL(triggered(bool)), this, SLOT(openActionClicked()));
    connect(ui->saveAction, SIGNAL(triggered(bool)), this, SLOT(saveActionClicked()));
    //Context menu
    connect(ui->graphicsView,
            SIGNAL(customContextMenuRequested(
                           const QPoint &)),
            this,
            SLOT(showContextMenu(
                         const QPoint &)));
    //Clear button
    connect(ui->clearBtn, SIGNAL(clicked(bool)), this, SLOT(clearBtnClicked()));
    connect(ui->closeCurveBtn, SIGNAL(clicked(bool)), this, SLOT(closeBtnClicked()));
    //Install event filters
    ui->graphicsView->installEventFilter(this);
}

void MainWindow::aboutActionClicked() {
    QMessageBox::information(this,
                             "О программе", "© Программа рисования кривых Безье, Ярных Роман, 2017\n"
                                     "1. Рисование кривых Безье\n"
                                     "2. Перемещение\n"
                                     "3. Замыкание\n"
    );
}

MainWindow::~MainWindow() {
    for (int i = 0; i < curves.size(); i++)
        delete curves[i];
    delete ui;
}

void MainWindow::saveActionClicked() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Сохранить кривые"), "",
                                                    tr("Кривые (*.json);;Все файлы (*)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, QString("Не возможно сохранить файл"), file.errorString());
    }
    QJsonArray array;
    for (auto &curve : curves) {
        array.append(curve->toJson());
    }
    QJsonDocument doc(array);
    file.write(doc.toJson());
    file.close();
}

void MainWindow::openActionClicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Сохранить кривые"), "",
                                                    tr("Кривые (*.json);;Все файлы (*)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, QString("Не возможно открыть файл"), file.errorString());
    }
    QJsonArray array = QJsonDocument::fromJson(file.readAll()).array();
    file.close();
    for (auto &&i : array) {
        if (i.toObject()["type"] == "BEZIER") {
            Bezier bezier = Bezier::fromJson(i.toObject());
            curves.push_back(&bezier);
        }
    }
    redraw();
}

void MainWindow::showContextMenu(const QPoint &pos) {
    QMenu contextMenu(tr("Действия"), ui->graphicsView);
    QAction addNewCurveAction("Добавить кривую", ui->graphicsView);
    QAction finishCurveAction("Завершить рисование", ui->graphicsView);
    connect(&addNewCurveAction, SIGNAL(triggered(bool)), this, SLOT(addNewCurve()));
    connect(&finishCurveAction, SIGNAL(triggered(bool)), this, SLOT(finishCurve()));
    contextMenu.addAction(&addNewCurveAction);
    contextMenu.addAction(&finishCurveAction);
    contextMenu.exec(mapToGlobal(pos));
}

void MainWindow::addNewCurve() {
    vector<QPointF> anchors;
    auto *bezier = new Bezier(anchors);
    curves.emplace_back(bezier);
    currentCurveIndex = curves.size() - 1;
    isDrawingMode = true;
}

void MainWindow::addNewPoint(const QPointF &point) {
    auto curve = curves[currentCurveIndex];
    curve->addAnchor(point);
    redraw();
}

void MainWindow::finishCurve() {
    isDrawingMode = false;
}

void MainWindow::redraw() {
    scene->clear();
    for (auto &curve : curves) {
        curve->paint(scene);
    }
}

bool MainWindow::eventFilter(QObject *target, QEvent *event) {
    if (target == ui->graphicsView) {
        if (event->type() == QEvent::MouseButtonPress && isDrawingMode) {
            auto *mouseEvent = dynamic_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                addNewPoint(
                        ui->graphicsView->mapFrom(ui->graphicsView, mouseEvent->pos())
                );
            }
        }
    }
    return QMainWindow::eventFilter(target, event);
}

void MainWindow::clearBtnClicked() {
    for (auto &curve : curves) {
        delete curve;
    }
    curves.clear();
    scene->clear();
    isDrawingMode = false;
}

void MainWindow::closeBtnClicked() {

}
