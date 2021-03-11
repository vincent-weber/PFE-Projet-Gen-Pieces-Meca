// Basé sur :
// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#ifndef PRINC_H
#define PRINC_H

#include "ui_princ.h"

class Princ : public QMainWindow, private Ui::Princ
{
    Q_OBJECT

public:
    explicit Princ(QWidget *parent = nullptr);
private slots:
    void on_gen_screw_button_clicked();
    void on_gen_nut_button_clicked();
    void on_gen_box_button_clicked();
    void on_gen_engines_button_clicked();
    void on_gen_box_angles_button_clicked();
    void on_gen_hinge_button_clicked();

signals:
    void run_gen_screw_button();
    void run_gen_nut_button();
    void run_gen_box_button();
    void run_gen_engines_button();
    void run_gen_box_angles_button();
    void run_gen_hinge_button();
};

#endif // PRINC_H
