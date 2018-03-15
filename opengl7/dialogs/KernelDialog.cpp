//
// Created by Max Heartfield on 15.03.18.
//

#include "KernelDialog.h"
#include "../FiltersPool.h"

void KernelDialog::setFilter() {
    float kernel[9];
    for (int i = 0; i < 9; i++)
        kernel[i] = k[i]->text().toFloat();
    filter = FiltersPool::getInstance()->kernel(kernel);
    close();
}

KernelDialog::KernelDialog(QWidget *parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout;
    kernelChooser = new QComboBox;
    kernelChooser->addItem("Sharpen");
    kernelChooser->addItem("Blur");
    mainLayout->addWidget(kernelChooser);
    for (int i = 0; i < 3; i++) {
        rows[i] = new QHBoxLayout;
        mainLayout->addLayout(rows[i]);
    }
    for (int i = 0; i < 9; i++) {
        k[i] = new QLineEdit;
        k[i]->setText("1");
        auto row = rows[i / 3];
        if (row == nullptr)
            rows[i / 3] = new QHBoxLayout;
        rows[i / 3]->addWidget(k[i]);
    }
    okButton = new QPushButton("OK");
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(setFilter()));
    connect(kernelChooser, SIGNAL(currentTextChange(QString&)), this, SLOT(chooseKernel(QString&)));
    mainLayout->addWidget(okButton);
    setLayout(mainLayout);
}

void KernelDialog::chooseKernel(QString& str){

}

