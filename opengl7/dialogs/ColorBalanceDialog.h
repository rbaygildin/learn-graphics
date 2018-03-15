//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_COLORBALANCEDIALOG_H
#define OPENGL_COLORBALANCEDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include "../filters/ColorBalance.h"

class ColorBalanceDialog : public QDialog {
Q_OBJECT
public:
    explicit ColorBalanceDialog(QWidget *parent = nullptr);

public slots:

    void setFilter();

public:
    ColorBalance *filter;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *mainLayout;
    QVBoxLayout *rLayout;
    QVBoxLayout *gLayout;
    QLabel *label;
    QLabel *rLabel;
    QLabel *gLabel;
    QLabel *bLabel;
    QSlider *rSlider;
    QSlider *gSlider;
    QSlider *bSlider;
    QPushButton *okButton;
    QVBoxLayout *bLayout;
};

#endif //OPENGL_COLORBALANCE_H
