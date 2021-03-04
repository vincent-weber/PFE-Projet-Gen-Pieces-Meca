// Basé sur :
// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "princ.h"
#include <QDebug>

Princ::Princ(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    connect(this, SIGNAL(run_gen_screw_button()), glarea, SLOT(run_gen_screw()));
    connect(this, SIGNAL(run_gen_nut_button()), glarea, SLOT(run_gen_nut()));
    connect(this, SIGNAL(run_gen_box_button()), glarea, SLOT(run_gen_box()));
    connect(this, SIGNAL(run_gen_box_angles_button()), glarea, SLOT(run_gen_box_angles()));
}

void Princ::on_gen_screw_button_clicked()
{
    emit run_gen_screw_button();
}

void Princ::on_gen_nut_button_clicked()
{
    emit run_gen_nut_button();
}

void Princ::on_gen_box_button_clicked()
{
    emit run_gen_box_button();
}

void Princ::on_gen_box_angles_button_clicked(){
    emit run_gen_box_angles_button();
}
