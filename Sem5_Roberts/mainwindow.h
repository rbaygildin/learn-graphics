#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <algorithm>
#include <QMainWindow>
#include <QSignalMapper>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "tetrahedroninput.h"
#include "figures/cube.h"
#include "figures/pyramid.h"
#include "figures/octahedron.h"
#include "figures/icosahedron.h"

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void createActions();

    void drawAxes();

    bool eventFilter(QObject *target, QEvent *event) override;

    void addCube(QPoint pos);

    void addPyramid(QPoint pos);

    void addOctahedron(QPoint pos);

    void addIcosahedron(QPoint pos);

    ~MainWindow() override;

private slots:

    void save();

    void open();

    void about();

    void showGraphicsViewMenu(QPoint pos);

    void showListWidgetMenu(QPoint pos);

    void redraw();

    void rotateX();

    void rotateY();

    void rotateZ();

    void scaleX();

    void scaleY();

    void scaleZ();

    void moveX();

    void moveY();

    void moveZ();

    void clear();

    void restore();

    void select(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    vector<IFigure *> figures;
    IFigure *selectedFigure;

    void addTetrahedron(QPoint point);
};

#endif // MAINWINDOW_H
