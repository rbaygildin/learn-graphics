#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <vector>
#include "figures/figure.h"
#include "figures/cube.h"
#include "figures/pyramid.h"
#include "figures/icosahedron.h"
#include "figures/octahedron.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;

public:
    void createActions();

public slots:
    void aboutMenuItemClicked();
    void showMenu(QPoint pos);
    void addCube();
    void addPyramid();
    void addOctahedron();
    void addIcosahedron();
    void redraw();
    void clear();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

private:
    vector<Figure*> figures;
};

#endif // MAINWINDOW_H
