#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <QVector>
#include <QVector3D>
#include "util.h"

class Grammar
{
public:
    Grammar(QString axiom);

    QString axiom;
    QString sentence = axiom;
    QVector<QVector<QString>> rules;

    bool isFirst();

    // Si -1 alors n'existe pas.
    float prev_l = -1;

    void addRule(QString in, QString out);
    void computeGrammar();

    //Creation d'une vis
    void createScrewRules();
    void createCyl(QString in, QVector3D param, QVector3D c, QVector3D rot);
    void createSphere(QString in, QVector3D c, QVector3D rot);
    void createCube(QString in, QVector3D c, QVector3D rot);
};

#endif // GRAMMAR_H
