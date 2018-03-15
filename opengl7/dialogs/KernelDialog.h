//
// Created by Max Heartfield on 15.03.18.
//

#ifndef OPENGL_KERNELDIALOG_H
#define OPENGL_KERNELDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include "../filters/Kernel.h"
#include <QComboBox>

class KernelDialog : public QDialog {
    Q_OBJECT
public:
    KernelDialog(QWidget *parent = nullptr);

public slots:

    void setFilter();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *rows[3];
    QLineEdit *k[9];
    QPushButton *okButton;

public:
    Kernel *filter;
    QComboBox *kernelChooser;
    void chooseKernel(QString &str);
};


#endif //OPENGL_KERNELDIALOG_H
