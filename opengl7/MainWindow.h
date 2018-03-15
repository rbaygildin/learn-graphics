//
// Created by Max Heartfield on 12.03.18.
//

#ifndef OPENGL_MAINWINDOW_H
#define OPENGL_MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QSlider>
#include "GLWidget.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public slots:

    void restoreImage();

    void shift();

    void openTextures();

    void openDicom();

    void aboutProgram();

    void applyBlur();

    void applyRed();

    void applyGreen();

    void applyBlue();

    void applySepia();

    void applyGamma();

    void applyAberration();

    void applyDistraction();

    void applyEmboss();

    void applyGrayscale();

    void applyReflection();

    void applySharpen();

    void applyThresholding();

    void applyRipple();

    void applyColorBalance();

    void applyKernel();

    void applyCanny();

    void applyLap();

    void saveImg();

private:
    void createMenu();

    void createActions();

    void createFilterDialogs();

    void createGLWidget();

private:
    QVBoxLayout *layout;
    QWidget *centralWidget;
    GLWidget *glWidget;
    QMenu *fileMenu;
    QMenu *programMenu;
    QAction *openAction;
    QAction *saveAction;
    QAction *aboutAction;
    QMenu *filtersMenu;

    QAction *thresholdingAction;
    QAction *abberationAction;
    QAction *blurAction;
    QAction *distractionAction;
    QAction *embossAction;
    QAction *gammaAction;
    QAction *grayscaleAction;
    QAction *greenFilterAction;
    QAction *reflectionAction;
    QAction *sepiaAction;
    QAction *sharpenAction;
    QAction *redAction;
    QAction *greenAction;
    QAction *blueAction;
    QAction *restoreAction;
    QAction *rippleAction;
    QAction *colorBalanceAction;
    QSlider *shiftSlider;
    QSlider *shiftYSlider;
    QAction *cannyAction;
    QAction *kernelAction;
    QAction *lapAction;
};


#endif //OPENGL_MAINWINDOW_H
