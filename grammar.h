#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <QVector>
#include <QVector3D>

class Grammar
{
public:
    Grammar(QString axiom);

    QString axiom;
    QString sentence = axiom;
    QVector<QVector<QString>> rules;

    void addRule(QString in, QString out);
    void computeGrammar();

    //Creation d'une vis
    void createScrewRules();
    void createHeadScrew();
    void createBodyScrew();
};

#endif // GRAMMAR_H
