//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_RIPPLEDIALOG_H
#define OPENGL_RIPPLEDIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include "../filters/ColorBalance.h"
#include "../filters/Ripple.h"

class RippleDialog : public QDialog {
Q_OBJECT
public:
    explicit RippleDialog(QWidget *parent = nullptr);

public slots:

    void setFilter();

public:
    Ripple *filter;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *rLayout;
    QHBoxLayout *gLayout;
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


#endif //OPENGL_RIPPLEDIALOG_H
