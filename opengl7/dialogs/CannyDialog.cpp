//
// Created by Max Heartfield on 15.03.18.
//

#include "CannyDialog.h"

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include "CannyDialog.h"
#include "../FiltersPool.h"

CannyDialog::CannyDialog(QWidget *parent) : QDialog(parent) {
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

void CannyDialog::setFilter() {
    filter = FiltersPool::getInstance()->canny(slider->value() / 255.0f);
    close();
}