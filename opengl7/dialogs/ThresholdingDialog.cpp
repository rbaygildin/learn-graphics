//
// Created by Max Heartfield on 15.03.18.
//

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include "ThresholdingDialog.h"
#include "../FiltersPool.h"

ThresholdingDialog::ThresholdingDialog(QWidget *parent) : QDialog(parent) {
    mainLayout = new QVBoxLayout;
    hBoxLayout = new QHBoxLayout;
    label = new QLabel("Threshold value");
    slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    slider->setMaximum(255);
    slider->setMinimum(0);
    okButton = new QPushButton("OK");
    hBoxLayout->addWidget(label);
    hBoxLayout->addWidget(slider);
    mainLayout->addLayout(hBoxLayout);
    mainLayout->addWidget(okButton);
    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(setFilter()));
    setLayout((QLayout *) mainLayout);
}

void ThresholdingDialog::setFilter() {
    filter = FiltersPool::getInstance()->thresholdingFilter(slider->value() / 255.0f);
    close();
}
