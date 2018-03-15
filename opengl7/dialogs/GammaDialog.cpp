//
// Created by Max Heartfield on 15.03.18.
//

#include "GammaDialog.h"
#include "../FiltersPool.h"

void GammaDialog::setFilter() {
    filter = FiltersPool::getInstance()->gammaFilter((slider->value() + 1.0f) / 5.0f);
    close();
}

GammaDialog::GammaDialog(QWidget *parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout;
    hBoxLayout = new QHBoxLayout;
    label = new QLabel("Gamma value");
    slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    slider->setMaximum(20);
    slider->setMinimum(0);
    okButton = new QPushButton("OK");
    hBoxLayout->addWidget(label);
    hBoxLayout->addWidget(slider);
    mainLayout->addLayout(hBoxLayout);
    mainLayout->addWidget(okButton);
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(setFilter()));
    setLayout((QLayout *) mainLayout);
}
