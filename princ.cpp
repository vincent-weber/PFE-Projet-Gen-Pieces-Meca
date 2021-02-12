// Basé sur :
// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "princ.h"
#include <QDebug>

Princ::Princ(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    connect(this, SIGNAL(run_gen_screw_button()), glarea, SLOT(run_gen_screw()));
    connect(this, SIGNAL(run_gen_nut_button()), glarea, SLOT(run_gen_nut()));
<<<<<<< HEAD
    connect(this, SIGNAL(run_gen_butterfly_button()), glarea, SLOT(run_gen_butterfly()));
=======
    connect(this, SIGNAL(run_gen_box_button()), glarea, SLOT(run_gen_box()));
>>>>>>> b-vincent
}

void Princ::on_gen_screw_button_clicked()
{
    emit run_gen_screw_button();
}

void Princ::on_gen_nut_button_clicked()
{
    emit run_gen_nut_button();
}

<<<<<<< HEAD
void Princ::on_gen_butterfly_button_clicked()
{
    qDebug() << __FUNCTION__;
    emit run_gen_butterfly_button();
=======
void Princ::on_gen_box_button_clicked()
{
    emit run_gen_box_button();
>>>>>>> b-vincent
}
