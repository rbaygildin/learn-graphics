//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_CANNYDIALOG_H
#define OPENGL_CANNYDIALOG_H


#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include "../utils.h"
#include "../filters/Canny.h"

class CannyDialog : public QDialog {
Q_OBJECT
public:
    CannyDialog(QWidget *parent = nullptr);

public slots:

    void setFilter();

public:
    Canny *filter;
    QHBoxLayout *hBoxLayout;
    QVBoxLayout *mainLayout;
    QLabel *label;
    QSlider *slider;
    QPushButton *okButton;
};


#endif //OPENGL_CANNYDIALOG_H
