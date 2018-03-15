//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_GAMMADIALOG_H
#define OPENGL_GAMMADIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>
#include "../filters/GammaFilter.h"

class GammaDialog : public QDialog {
Q_OBJECT
public:
    GammaDialog(QWidget *parent = nullptr);

public slots:

    void setFilter();

public:
    GammaFilter *filter;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *mainLayout;
    QLabel *label;
    QSlider *slider;
    QPushButton *okButton;
};


#endif //OPENGL_GAMMADIALOG_H
