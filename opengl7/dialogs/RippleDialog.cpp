//
// Created by Max Heartfield on 15.03.18.
//

#include "RippleDialog.h"
#include "../FiltersPool.h"

void RippleDialog::setFilter() {
    float t = rSlider->value() / 4.0f;
    float s = gSlider->value() / 40.0f;
    filter = FiltersPool::getInstance()->ripple(t, s);
    close();
}

RippleDialog::RippleDialog(QWidget *parent) : QDialog(parent){
    mainLayout = new QVBoxLayout;
    hBoxLayout = new QHBoxLayout;
    rLayout = new QHBoxLayout;
    gLayout = new QHBoxLayout;
    rLabel = new QLabel("Time");
    gLabel = new QLabel("Step");


    rSlider = new QSlider;
    rSlider->setOrientation(Qt::Horizontal);
    rSlider->setMaximum(40);
    rSlider->setMinimum(1);

    gSlider = new QSlider;
    gSlider->setOrientation(Qt::Horizontal);
    gSlider->setMaximum(40);
    gSlider->setMinimum(1);

    rLayout->addWidget(rSlider);
    rLayout->addWidget(rLabel);

    gLayout->addWidget(gSlider);
    gLayout->addWidget(gLabel);


    okButton = new QPushButton("OK");

    mainLayout->addLayout(rLayout);
    mainLayout->addLayout(gLayout);
    mainLayout->addWidget(okButton);


    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(setFilter()));
    setLayout((QLayout *) mainLayout);
}
