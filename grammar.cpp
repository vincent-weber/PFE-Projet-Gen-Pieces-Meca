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
    QVector3D rot(PI/2,PI/2,0); QVector3D c(0, 10, 0);

    createCyl("T", QVector3D(5,2,20), c, rot);
    createCyl("B", QVector3D(2,7,20), c, rot);
}

//Cylinder : float rad, float l, float prec, V3 c, V3 rot
void Grammar::createCyl(QString in, QVector3D param, QVector3D c, QVector3D rot){

    qDebug() << c;
    if(!isFirst()) {
        c[1] -= prev_l/2 + param[1]/2;
    }
    if(isFirst()) prev_l = param[1];



    QString out = "cyl(" + QString::number(param[0]) + "," + QString::number(param[1]) + "," + QString::number(param[2]) + ")";
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
