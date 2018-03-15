//
// Created by Max Heartfield on 12.03.18.
//

#include "MainWindow.h"
#include "FiltersPool.h"
#include "dialogs/ThresholdingDialog.h"
#include "dialogs/GammaDialog.h"
#include "dialogs/ColorBalanceDialog.h"
#include "dialogs/RippleDialog.h"
#include "dialogs/KernelDialog.h"
#include "dialogs/CannyDialog.h"

MainWindow::MainWindow(QWidget *parent) {
    createMenu();
    createGLWidget();
    auto hbox = new QHBoxLayout;
    shiftSlider = new QSlider(Qt::Horizontal);
    shiftSlider->setMinimum(0);
    shiftSlider->setMaximum(100);
    connect(shiftSlider, SIGNAL(valueChanged(int)), this, SLOT(shift()));

    shiftYSlider = new QSlider(Qt::Horizontal);
    shiftYSlider->setMinimum(0);
    shiftYSlider->setMaximum(100);
    connect(shiftYSlider, SIGNAL(valueChanged(int)), this, SLOT(shift()));


    hbox->addWidget(new QLabel("Shift X"));
    hbox->addWidget(shiftSlider);
    hbox->addWidget(new QLabel("Shift Y"));
    hbox->addWidget(shiftYSlider);

    layout = new QVBoxLayout;
    layout->addLayout(hbox);
    layout->addWidget(glWidget);
    centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("OpenGL 7");
    setMinimumSize(500, 500);
}

MainWindow::~MainWindow() = default;


void MainWindow::shift() {
    glWidget->setShift(shiftSlider->value() / 100.0f, shiftYSlider->value() / 100.0f);
}

void MainWindow::openTextures() {
    auto fileName = QFileDialog::getOpenFileNames(this, tr("Open textures"), QDir::currentPath(),
                                                  tr("Image Files (*.png *.jpg *.bmp, *jpeg, *dcm)"));
    if (fileName.length() != 0) {
        glWidget->setCurrentTexture(fileName);
    }
}

void MainWindow::openDicom() {

}

void MainWindow::restoreImage() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->original());
}

void MainWindow::applyRed() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->redFilter());
}

void MainWindow::applyGreen() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->greenFilter());
}

void MainWindow::applyBlue() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->blueFilter());
}

void MainWindow::applyBlur() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->blurFilter());
}

void MainWindow::applySepia() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->sepiaFilter());
}

void MainWindow::applyGamma() {
    auto dialog = new GammaDialog();
    dialog->exec();
    auto filter = dialog->filter;
    if (filter != nullptr)
        glWidget->setCurrentFilter(filter);
}

void MainWindow::aboutProgram() {
    QMessageBox::information(this, "Information", "OpenGL 7 - Image processing\n©Yarnykh Roman, 2018");
}

void MainWindow::createMenu() {
    //Menus
    fileMenu = new QMenu(tr("File"));
    filtersMenu = new QMenu(tr("Filters"));
    programMenu = new QMenu(tr("Program"));
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(filtersMenu);
    menuBar()->addMenu(programMenu);
    createActions();
    menuBar()->setNativeMenuBar(false);
}

void MainWindow::createGLWidget() {
    glWidget = new GLWidget(this);
}

void MainWindow::createActions() {
    //File Actions
    openAction = new QAction("Open");
    saveAction = new QAction("Save");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    //Program actions
    aboutAction = new QAction("About");
    programMenu->addAction(aboutAction);

    //Filter actions
    restoreAction = new QAction("Restore image");
    redAction = new QAction("Red filter");
    greenAction = new QAction("Green filter");
    blueAction = new QAction("Blue filter");
    sepiaAction = new QAction("Sepia");
    blurAction = new QAction("Blur");
    gammaAction = new QAction("Gamma");
    abberationAction = new QAction("Aberration");
    distractionAction = new QAction("Distraction");
    thresholdingAction = new QAction("Thresholding");
    embossAction = new QAction("Emboss");
    grayscaleAction = new QAction("Grayscale");
    reflectionAction = new QAction("Reflection");
    sharpenAction = new QAction("Sharpen");
    rippleAction = new QAction("Ripple");
    kernelAction = new QAction("Kernel");
    cannyAction = new QAction("Canny");
    lapAction = new QAction("Laplasian");
    colorBalanceAction = new QAction("Color balance");

    filtersMenu->addAction(restoreAction);
    filtersMenu->addAction(redAction);
    filtersMenu->addAction(greenAction);
    filtersMenu->addAction(blueAction);
    filtersMenu->addAction(sepiaAction);
    filtersMenu->addAction(blurAction);
    filtersMenu->addAction(gammaAction);
    filtersMenu->addAction(abberationAction);
    filtersMenu->addAction(distractionAction);
    filtersMenu->addAction(thresholdingAction);
    filtersMenu->addAction(embossAction);
    filtersMenu->addAction(grayscaleAction);
    filtersMenu->addAction(reflectionAction);
    filtersMenu->addAction(sharpenAction);
    filtersMenu->addAction(rippleAction);
    filtersMenu->addAction(kernelAction);
    filtersMenu->addAction(cannyAction);
    filtersMenu->addAction(lapAction);
    filtersMenu->addAction(colorBalanceAction);

    //Events
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openTextures()));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveImg()));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(aboutProgram()));

    connect(restoreAction, SIGNAL(triggered(bool)), this, SLOT(restoreImage()));
    connect(redAction, SIGNAL(triggered(bool)), this, SLOT(applyRed()));
    connect(greenAction, SIGNAL(triggered(bool)), this, SLOT(applyGreen()));
    connect(blueAction, SIGNAL(triggered(bool)), this, SLOT(applyBlue()));
    connect(sepiaAction, SIGNAL(triggered(bool)), this, SLOT(applySepia()));
    connect(blurAction, SIGNAL(triggered(bool)), this, SLOT(applyBlur()));
    connect(gammaAction, SIGNAL(triggered(bool)), this, SLOT(applyGamma()));
    connect(abberationAction, SIGNAL(triggered(bool)), this, SLOT(applyAberration()));
    connect(distractionAction, SIGNAL(triggered(bool)), this, SLOT(applyDistraction()));
    connect(thresholdingAction, SIGNAL(triggered(bool)), this, SLOT(applyThresholding()));
    connect(embossAction, SIGNAL(triggered(bool)), this, SLOT(applyEmboss()));
    connect(grayscaleAction, SIGNAL(triggered(bool)), this, SLOT(applyGrayscale()));
    connect(reflectionAction, SIGNAL(triggered(bool)), this, SLOT(applyReflection()));
    connect(sharpenAction, SIGNAL(triggered(bool)), this, SLOT(applySharpen()));
    connect(rippleAction, SIGNAL(triggered(bool)), this, SLOT(applyRipple()));
    connect(kernelAction, SIGNAL(triggered(bool)), this, SLOT(applyKernel()));
    connect(cannyAction, SIGNAL(triggered(bool)), this, SLOT(applyCanny()));
    connect(lapAction, SIGNAL(triggered(bool)), this, SLOT(applyLap()));
    connect(colorBalanceAction, SIGNAL(triggered(bool)), this, SLOT(applyColorBalance()));
}

void MainWindow::createFilterDialogs() {

}

void MainWindow::applyAberration() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->aberrationFilter());
}

void MainWindow::applyDistraction() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->distractionFilter());
}

void MainWindow::applyEmboss() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->emboss());
}

void MainWindow::applyGrayscale() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->grayscaleFilter());
}

void MainWindow::applyReflection() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->reflectionFilter());
}

void MainWindow::applySharpen() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->sharpenFilter());
}

void MainWindow::applyThresholding() {
//    glWidget->setCurrentFilter(FiltersPool::getInstance()->thresholdingFilter());
    auto dialog = new ThresholdingDialog();
    dialog->exec();
    auto filter = dialog->filter;
    if (filter != nullptr)
        glWidget->setCurrentFilter(filter);
}

void MainWindow::applyColorBalance() {
    auto dialog = new ColorBalanceDialog();
    dialog->exec();
    auto filter = dialog->filter;
    if (filter != nullptr)
        glWidget->setCurrentFilter(filter);
}

void MainWindow::applyRipple() {
    auto dialog = new RippleDialog();
    dialog->exec();
    auto filter = dialog->filter;
    if (filter != nullptr)
        glWidget->setCurrentFilter(filter);
}

void MainWindow::applyKernel() {
    auto dialog = new KernelDialog();
    dialog->exec();
    auto filter = dialog->filter;
    if (filter != nullptr)
        glWidget->setCurrentFilter(filter);
}

void MainWindow::saveImg() {
    QString filename = QFileDialog::getSaveFileName(this, "Save File", QDir::currentPath(),
                                                    "JPEG Image (*.jpg *.jpeg)");
    //QImage image = mpPlot->grabFrameBuffer( );
    //QPixmap image = mpPlot->renderPixmap( );
    auto image = QPixmap::grabWidget(glWidget, 0, 0, glWidget->width(), glWidget->height());
    if (!image.save(filename, "JPG")) {
        QMessageBox::warning(this, "Save Image", "Error saving image.");
    }
}

void MainWindow::applyCanny() {
    auto dialog = new CannyDialog();
    dialog->exec();
    auto filter = dialog->filter;
    if (filter != nullptr)
        glWidget->setCurrentFilter(filter);
}

void MainWindow::applyLap() {
    glWidget->setCurrentFilter(FiltersPool::getInstance()->lap());
}
