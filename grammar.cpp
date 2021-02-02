#include "grammar.h"
#include <QDebug>
#include <random>

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

    std::random_device rd;
    std::uniform_int_distribution<int> distForm{1, 10};
    int form = distForm(rd);

    if(form < 5) {
        addRule(QString("V"), QString("S+T+B"));
    } else {
        addRule(QString("V"), QString("T+B"));
    }

    QVector3D rot(PI/2,PI/2,0); QVector3D c(0, 10, 0);





    int distRad = std::uniform_int_distribution<int>{2, 7}(rd);
    int distL = std::uniform_int_distribution<int>{2, 3}(rd);
    int distPrec = std::uniform_int_distribution<int>{5, 15}(rd);
    int distRad2 = std::uniform_int_distribution<int>{1, distRad-2}(rd);
    int distRad3 = std::uniform_int_distribution<int>{1, 2}(rd);
    distL = std::uniform_int_distribution<int>{3, 6}(rd);
    qDebug() << "FORM" << form;



    createCyl("T", QVector3D(distRad, distL, distPrec), c, rot);
    if(form < 5) {
        c[1] += distL;
        createSphere("S", QVector3D(distRad3, distL, 20), c, rot);
    }
    createCyl("B", QVector3D(distRad2,distL,20), c, rot);




}

//Cylinder : float rad, float l, float prec, V3 c, V3 rot
void Grammar::createCyl(QString in, QVector3D param, QVector3D c, QVector3D rot){

    if(!isFirst()) {
        c[1] -= prev_l/2 + param[1]/2;
        prev_l += param[1];
    }
    if(isFirst()) {
        prev_l = param[1];
    }

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
void Grammar::createCube(QString in, QVector3D param, QVector3D c, QVector3D rot){

    QString out = "cub(" + QString::number(param[0]) + "," + QString::number(param[1]) + "," + QString::number(param[2]) + ")";
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
void Grammar::createSphere(QString in, QVector3D param, QVector3D c, QVector3D rot){

    if(!isFirst()) {
        c[1] -= prev_l/2 + param[0]/2;
        prev_l += param[0];
    }
    if(isFirst()) {
        prev_l = param[0];
    }

    QString out = "sph(" + QString::number(param[0]) + "," + QString::number(param[1]) + "," + QString::number(param[2]) + ")";
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
