#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>
#include "figures/cube.h"
#include "figures/pyramid.h"
#include "figures/octahedron.h"
#include "figures/icosahedron.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Fig{CUBE, PYRAMID, OCT, ICOS};
    explicit MainWindow(QWidget *parent = 0);
    void createActions();
    void createContextMenu();
    void drawAxes();
    ~MainWindow() override;

private slots:
    void aboutMenuItemClicked();
    void contextMenuRequested(QPoint pos);
    void redraw();
    void drawCube();
    void drawPyramid();
    void drawOctahedron();
    void drawIcosahedron();
    void setCube();
    void setPyramid();
    void setOctahedron();
    void setIcosahedron();
    void clear();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QSignalMapper *pSignalMapper;
    Fig fig;
    bool isRotating = false;
};

#endif // MAINWINDOW_H
