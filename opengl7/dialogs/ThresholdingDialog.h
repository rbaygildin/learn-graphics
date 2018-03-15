//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_THRESHOLDINGDIALOG_H
#define OPENGL_THRESHOLDINGDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include "../filters/ThresholdingFilter.h"

class ThresholdingDialog : public QDialog {
Q_OBJECT
public:
    ThresholdingDialog(QWidget *parent = nullptr);

public slots:
    void setFilter();

public:
    ThresholdingFilter *filter;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *mainLayout;
    QLabel *label;
    QSlider *slider;
    QPushButton *okButton;
};


#endif //OPENGL_THRESHOLDINGDIALOG_H
