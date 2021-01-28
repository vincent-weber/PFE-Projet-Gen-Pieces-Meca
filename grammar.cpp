#include "grammar.h"
#include <QDebug>

Grammar::Grammar(QString axiom)
{
    this->axiom = axiom;
    this->sentence = axiom;
}

void Grammar::addRule(QString in, QString out){
    QVector<QString> rule;
    rule.push_back(in); rule.push_back(out);
    rules.push_back(rule);
}

void Grammar::createScrewRules(){
    addRule(QString(axiom), QString("V"));
    addRule(QString("V"), QString("T+B"));
    createHeadScrew(); createBodyScrew();
}

//Cylinder : float rad, float diam, float prec, V3 c, V3 rot
void Grammar::createHeadScrew(){
    float rad(.0), diam(.0), prec(.0);
    QVector3D c(0,0,0), rot(0,0,0);

    QString in, out;

    in = "T";
    out = "cyl(" + QString::number(rad) + QString::number(diam) + QString::number(prec) + ")";
    out += "[c(";
    for(int i = 0; i < 3; i++) {
        out += QString::number(c[i]);
        if(i < 2) out += ",";
    }
    out += "[rot(";
    for(int i = 0; i < 3; i++) {
        out += QString::number(rot[i]);
        if(i < 2) out += ",";
    }
    out += "]";

    addRule(in, out);
}

void Grammar::createBodyScrew(){
    float rad(.0), diam(.0), prec(.0);
    QVector3D c(0,0,0), rot(0,0,0);

    QString in, out;

    in = "B";
    out = "cyl(" + QString::number(rad) + QString::number(diam) + QString::number(prec) + ")";
    out += "[c(";
    for(int i = 0; i < 3; i++) {
        out += QString::number(c[i]);
        if(i < 2) out += ",";
    }
    out += "[rot(";
    for(int i = 0; i < 3; i++) {
        out += QString::number(rot[i]);
        if(i < 2) out += ",";
    }
    out += "]";

    addRule(in, out);
}

//Permet d'appliquer les regles existantes à la phrase courante.
void Grammar::computeGrammar(){
    QString newSentence = "";

    for(int i = 0; i < rules.size(); i++){
        for(int j = 0; j < sentence.size(); j++){
            if(sentence.at(j) == rules[i][0]){
                for(int k = 0; k < rules[i][1].size(); k++){
                    newSentence += rules[i][1].at(k);
                }
            }
        }
    }

    this->sentence = newSentence;
    qDebug() << this->sentence;
}
