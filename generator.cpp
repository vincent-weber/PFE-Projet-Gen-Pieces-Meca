#include "generator.h"

QHash<QString, QVector<QString>> Generator::rules;

void Generator::initRules() {
    rules.insert("Screw", {"ScrewBodyCyl+ScrewHeadCyl", "ScrewBodyCyl+ScrewHeadCyl6", "ScrewBodyCyl+ScrewHeadCub", "ScrewBodyCyl+ScrewHeadCyl6+ScrewInterCyl6"});
    rules.insert("Nut", {"NutMainCyl-NutIntersectCyl"});
    rules.insert("Box", {"JE SUIS", "QUELQUUN"});
    rules.insert("Butterfly", {"ButterflyBoby+LeftWing+RightWing"});
    rules.insert("Box", {"BoiteCube+VisAnglesBoiteCub"});
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

float Generator::computeParameter(float param, std::random_device& rd, float min, float max) {
    if (param == -1) {
        return std::uniform_real_distribution<float>{min, max}(rd);
    }
    else {
        return param;
    }
}
int Generator::computeParameter(int param, std::random_device& rd, int min, int max) {
    if (param == -1) {
        return std::uniform_int_distribution<int>{min, max}(rd);
    }
    else {
        return param;
    }
}

QString Generator::createLeafRulesMultiple(QVector<QString>& primitives, QString op_bools, QVector<QVector3D>& params, QVector<QVector3D>& centers, QVector<QVector3D>& rots) {
    QString out = "";
    int size = primitives.size();
    for (int index_pr = 0 ; index_pr < size ; ++index_pr) {
        qDebug() << QString::number(params[index_pr][0]) << "," << QString::number(params[index_pr][1]) << "," << QString::number(params[index_pr][2]) << ")";
        out += primitives[index_pr] + "(" + QString::number(params[index_pr][0]) + "," + QString::number(params[index_pr][1]) + "," + QString::number(params[index_pr][2]) + ")";
        out += "[cen(";
        out += QString::number(centers[index_pr].x()); out += ',';
        out += QString::number(centers[index_pr].y()); out += ',';
        out += QString::number(centers[index_pr].z());
        out += ")";
        out += "rot(";
        for(int index_rot = 0; index_rot < 3; index_rot++) {
            out += QString::number(rots[index_pr][index_rot]);
            if(index_rot < 2) out += ",";
        }
        out += ")";
        out += "]";

        if (index_pr != size-1) {
            out += op_bools[index_pr];
        }
    }
    return out;
}

void Generator::createLeafRulesSingle(QString primitive_type, QString in, QVector3D param, QVector3D c, QVector3D rot){

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
