#include "grammar.h"
#include <QDebug>
Grammar::Grammar(QString axiom)
{
    this->axiom = axiom;
    this->sentence = axiom;
}

void Grammar::addRule(QString in, QString out){
    rulesH[in].push_back(out);
}

void Grammar::createScrewRules(){
    addRule(axiom, "V");
    addRule("V", "T+B");

    QVector3D rot(PI/2,PI/2,0);

    createCyl("T", createParam(CYLINDRE), c, rot);
    QVector3D paramB = createParamB();
    c->setY(c->y() - (prev_l/2 + paramB[1]/2));
    createCyl("B", paramB, c, rot);
}

QVector3D Grammar::createParamB(){
    return QVector3D(std::uniform_int_distribution<int>{1,3}(rd),
                std::uniform_int_distribution<int>{5,10}(rd),
                20
           );
}

QVector3D Grammar::createParam(TypeForm type){
    if (type == CYLINDRE){
        return QVector3D(std::uniform_int_distribution<int>{4,5}(rd),
                    std::uniform_int_distribution<int>{2,3}(rd),
                    std::uniform_int_distribution<int>{5, 20}(rd)
               );
    } else if (type == SPHERE){
        return QVector3D(std::uniform_int_distribution<int>{1,3}(rd),
                         20,
                         20
               );
    }
}

void Grammar::createNutRules(){
    addRule(axiom, "N");
    addRule("N", "C-T");

    QVector3D rot(PI/2, PI/2, 0);
    createCyl("C", createParam(CYLINDRE), c, rot);
    createCyl("T", createParamB(), c, rot);
}

//Cylinder : float rad, float l, float prec, V3 c, V3 rot
void Grammar::createCyl(QString in, QVector3D param, QVector3D *c, QVector3D rot){

    prev_l = param[1];

    QString out = "cyl(" + QString::number(param[0]) + "," + QString::number(param[1]) + "," + QString::number(param[2]) + ")";
    out += "[cen(";
    out += QString::number(c->x()); out += ',';
    out += QString::number(c->y()); out += ',';
    out += QString::number(c->z());
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
void Grammar::createCube(QString in, QVector3D param, QVector3D *c, QVector3D rot){

    QString out = "cub(" + QString::number(param[0]) + "," + QString::number(param[1]) + "," + QString::number(param[2]) + ")";
    out += "[cen(";

    out += QString::number(c->x()); out += ',';
    out += QString::number(c->y()); out += ',';
    out += QString::number(c->z());

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

//Sphere : float rad, float stack_c, float sector_c, V3 c, V3 rot
void Grammar::createSphere(QString in, QVector3D param, QVector3D *c, QVector3D rot){


    prev_l = param[0];


    QString out = "sph(" + QString::number(param[0]) + "," + QString::number(param[1]) + "," + QString::number(param[2]) + ")";
    out += "[cen(";
    out += QString::number(c->x()); out += ',';
    out += QString::number(c->y()); out += ',';
    out += QString::number(c->z());
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

//Permet d'appliquer les regles existantes à la phrase courante.
void Grammar::computeGrammar(){
    int num;
    bool found = true;

    while(found){
        found = false;
        for(int i = 0; i < sentence.size(); i++){
            if(rulesH.contains(sentence.at(i))){
                found = true;
    //            qDebug() << "Taille :" << rulesH.value(sentence.at(i)).length();
                if(rulesH.value(sentence.at(i)).length() > 0) {
                    num = std::uniform_int_distribution<int>{0, rulesH.value(sentence.at(i)).length()-1}(rd);
                } else num = 0;
    //            qDebug() << "INDEX ALEATOIRE" << num;
                sentence.replace(QString(sentence.at(i)), rulesH.value(sentence.at(i))[num]);
            }
        }

    }



}

bool Grammar::isFirst(){
    return (prev_l == -1);
}
