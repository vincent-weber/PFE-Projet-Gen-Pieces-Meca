#include "generator.h"

QHash<QString, QVector<QString>> Generator::rules;

void Generator::initRules() {
    rules.insert("Screw", {"ScrewBodyCyl+ScrewHeadCyl", "ScrewBodyCyl+ScrewHeadCyl6", "ScrewBodyCyl+ScrewHeadCub", "ScrewBodyCyl+ScrewHeadCyl6+ScrewInterCyl6"});
    rules.insert("Nut", {"NutMainCyl-NutIntersectCyl"});
    rules.insert("Box", {"JE SUIS", "QUELQUUN"});
}

void Generator::createRules() {
    int nb_part_possibilities = rules.find(generator_name)->count();
    unsigned index = std::uniform_int_distribution<int>{0,nb_part_possibilities-1}(rd_gen);
    sentence = rules.find(generator_name)->at(index);
    QStringList primitives_str = sentence.split(QRegExp("\\-|\\+|\\*"));
    for (int i = 0 ; i < primitives_str.size() ; ++i) {
        generate(primitives_str.at(i));
    }
}

void Generator::createLeafRules(QString primitive_type, QString in, QVector3D param, QVector3D c, QVector3D rot){

    QString out = primitive_type + "(" + QString::number(param[0]) + "," + QString::number(param[1]) + "," + QString::number(param[2]) + ")";
    out += "[cen(";
    out += QString::number(c.x()); out += ',';
    out += QString::number(c.y()); out += ',';
    out += QString::number(c.z());
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

void Generator::computeSentence() {
    QStringList primitives_str = sentence.split(QRegExp("\\-|\\+|\\*"));
    for (int i = 0 ; i < primitives_str.size() ; ++i) {
        if(!rules.value(primitives_str[i]).isEmpty()){
            sentence.replace(primitives_str[i], rules.value(primitives_str[i])[0]);
        }
    }
}
