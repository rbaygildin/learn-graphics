#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonArray>
#include <QMouseEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include "curves/Bezier.h"

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

private slots:
    void aboutActionClicked();
    void saveActionClicked();
    void openActionClicked();
    void showContextMenu(const QPoint &pos);
    void addNewCurve();
    void addNewPoint(const QPointF &point);
    void clearBtnClicked();
    void closeBtnClicked();
    void finishCurve();
private:
    void redraw();
private:
    QGraphicsScene *scene;
    Ui::MainWindow *ui;
    vector<Curve*> curves;
    long currentCurveIndex;
    bool isDrawingMode;
    bool eventFilter(QObject *target, QEvent *event) override;
};

#endif // MAINWINDOW_H
