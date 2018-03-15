//
// Created by Max Heartfield on 15.03.18.
//

#include "ColorBalanceDialog.h"
#include "../FiltersPool.h"

ColorBalanceDialog::ColorBalanceDialog(QWidget *parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout;
    hBoxLayout = new QHBoxLayout;
    rLayout = new QVBoxLayout;
    gLayout = new QVBoxLayout;
    bLayout = new QVBoxLayout;
    rLabel = new QLabel("Red level");
    gLabel = new QLabel("Green level");
    bLabel = new QLabel("Blue level");


    rSlider = new QSlider;
    rSlider->setOrientation(Qt::Vertical);
    rSlider->setMaximum(20);
    rSlider->setMinimum(-20);

    gSlider = new QSlider;
    gSlider->setOrientation(Qt::Vertical);
    gSlider->setMaximum(20);
    gSlider->setMinimum(-20);

    bSlider = new QSlider;
    bSlider->setOrientation(Qt::Vertical);
    bSlider->setMaximum(20);
    bSlider->setMinimum(-20);

    rLayout->addWidget(rSlider);
    rLayout->addWidget(rLabel);

    gLayout->addWidget(gSlider);
    gLayout->addWidget(gLabel);

    bLayout->addWidget(bSlider);
    bLayout->addWidget(bLabel);


    okButton = new QPushButton("OK");

    hBoxLayout->addLayout(rLayout);
    hBoxLayout->addLayout(gLayout);
    hBoxLayout->addLayout(bLayout);

    mainLayout->addLayout(hBoxLayout);
    mainLayout->addWidget(okButton);


    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(setFilter()));
    setLayout((QLayout *) mainLayout);
}

void ColorBalanceDialog::setFilter() {
    float r = rSlider->value() / 40.0f;
    float g = gSlider->value() / 40.0f;
    float b = bSlider->value() / 40.0f;
    filter = FiltersPool::getInstance()->colorBalance(r, g, b);
    close();
}
