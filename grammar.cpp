#include "grammar.h"
#include <QDebug>

//A la relecture QString::number(sentence.at(0).unicode(), 10); Pour avoir le code ASCII d'un caractere.
// cyl --> c = 67, y = 89 , l = 76 ---> cyl = 67 + 89 + 76 = 232. Si 232 alors on créé un cylindre.
//Chaque objet est représenté par 3 caractere dans la grammaire.

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
    QVector3D rot(0,0,0);
    createCyl("T", QVector3D(0,0,0), rot); createCyl("B", QVector3D(0,0,prev_l), rot);
}

//Cylinder : float rad, float l, float prec, V3 c, V3 rot
void Grammar::createCyl(QString in, QVector3D c, QVector3D rot){
    float rad(1), l(5), prec(.5);

    if(!isFirst()) c[2] += l/2;
    prev_l = l;

    QString out = "cyl(" + QString::number(rad) + "," + QString::number(l) + "," + QString::number(prec) + ")";
    out += "[cen(";
    for(int i = 0; i < 3; i++) {
        out += QString::number(c[i]);
        if(i < 2) out += ",";
    }
    out += ")";
    out += "rot(";
    for(int i = 0; i < 3; i++) {
        out += QString::number(rot[i]);
        if(i < 2) out += ",";
    }
    out += ")";
    out += "]";

    addRule(in, out);
}

//Cuboid : float l, float w, float h, V3 c, V3 rot
void Grammar::createCube(QString in, QVector3D c, QVector3D rot){
    float l(.0), w(.0), h(.0);

    QString out = "cub(" + QString::number(l) + "," + QString::number(w) + "," + QString::number(h) + ")";
    out += "[cen(";
    for(int i = 0; i < 3; i++) {
        out += QString::number(c[i]);
        if(i < 2) out += ",";
    }
    out += ")";
    out += "[rot(";
    for(int i = 0; i < 3; i++) {
        out += QString::number(rot[i]);
        if(i < 2) out += ",";
    }
    out += ")";
    out += "]";

    addRule(in, out);
}

//Sphere : float rad, float stack_c, float sector_c, V3 c, V3 rot
void Grammar::createSphere(QString in, QVector3D c, QVector3D rot){
    float rad(.0), stack(.0), sector(.0);

    QString out = "sph(" + QString::number(rad) + QString::number(stack) + QString::number(sector) + ")";
    out += "[cen(";
    for(int i = 0; i < 3; i++) {
        out += QString::number(c[i]);
        if(i < 2) out += ",";
    }
    out += ")";
    out += "[rot(";
    for(int i = 0; i < 3; i++) {
        out += QString::number(rot[i]);
        if(i < 2) out += ",";
    }
    out += ")";
    out += "]";

    addRule(in, out);
}

//Permet d'appliquer les regles existantes à la phrase courante.
void Grammar::computeGrammar(){
    QString newSentence = "";

    for(int i = 0; i < sentence.size(); i++){
        bool found = false;
        for(int j = 0; j < rules.size(); j++){
            if(sentence.at(i) == rules[j][0]){
                found = true;
                for(int k = 0; k < rules[j][1].size(); k++){
                    newSentence += rules[j][1].at(k);
                }
            }
        }
        if(!found) newSentence += sentence.at(i);
    }

    this->sentence = newSentence;
    qDebug() << this->sentence;
}

bool Grammar::isFirst(){
    return (prev_l == -1);
}
