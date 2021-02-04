#include "generator.h"

QHash<QString, QVector<QString>> Generator::rules;

void Generator::initRules() {
    rules.insert("Screw", {"Sphere+ScrewHead+ScrewBody", "ScrewHead+ScrewBody"});
    rules.insert("Nut", {"BONJOUR", "CA VA"});
    rules.insert("Box", {"JE SUIS", "QUELQUUN"});
}

void Generator::createLeafRules(QString primitive_type, QString in, QVector3D param, QVector3D *c, QVector3D rot){

    QString out = primitive_type + "(" + QString::number(param[0]) + "," + QString::number(param[1]) + "," + QString::number(param[2]) + ")";
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

    rules.insert(in, {out});
}
