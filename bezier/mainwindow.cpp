#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);
    //About action event
    connect(ui->aboutProgramAction, SIGNAL(triggered(bool)), this, SLOT(aboutActionClicked()));
}

void MainWindow::aboutActionClicked(){
    QMessageBox::information(this,
                             "О программе", "© Программа рисования кривых Безье, Ярных Роман, 2017\n"
                                            "1. Рисование кривых Безье\n"
                                            "2. Перемещение\n"
                                            "3. Замыкание\n"
                             );
}

MainWindow::~MainWindow()
{
    delete ui;
}
