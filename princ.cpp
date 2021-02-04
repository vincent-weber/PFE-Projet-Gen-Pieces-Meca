// Basé sur :
// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "princ.h"
#include <QDebug>

Princ::Princ(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    connect(this, SIGNAL(run_grammar()), glarea, SLOT(runGram()));
}

void Princ::on_run_button_clicked()
{
    qDebug() << __FUNCTION__;
    emit run_grammar();
}
