#include "generator.h"

QHash<QString, QVector<QString>> Generator::rules;

void Generator::initRules() {
    rules.insert("Screw", {"ScrewBodyCyl+ScrewHeadCyl", "ScrewBodyCyl+ScrewHeadCyl6", "ScrewBodyCyl+ScrewHeadCub", "ScrewBodyCyl+ScrewHeadCyl6+ScrewInterCyl6"});
    rules.insert("Nut", {"NutMainCyl-NutIntersectCyl"});
    rules.insert("Butterfly", {"ButterflyBoby+LeftWing+RightWing"});
//    rules.insert("Box", {"BoiteCube+VisAnglesBoiteCub"});
    rules.insert("Box", {/*"BoiteCube+VisAnglesBoiteCub", */"BoiteRelief+AncrageGrille3x3"});
}

void Generator::createParams() {
    int nb_part_possibilities = rules.find(generator_name)->count();
    unsigned index = std::uniform_int_distribution<int>{0,nb_part_possibilities-1}(rd_gen);
    base_sentence = rules.find(generator_name)->at(index);
    sentence = base_sentence;
    primitives_str = sentence.split(QRegExp("\\-|\\+|\\*"));
    for (int i = 0 ; i < primitives_str.size() ; ++i) {
        generateParams(primitives_str.at(i));
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

QString Generator::createLeafRulesMultiple(QVector<QString>& primitives, QString op_bools, QVector<QVector<float>>& params, QVector<QVector3D>& centers, QVector<QVector3D>& rots) {
    QString out = "";
    int size = primitives.size();
    for (int index_pr = 0 ; index_pr < size ; ++index_pr) {
        //changer params en Qvector<Qvector<float>> dans le cas ou on a plusieurs paramètres ?
        out += "(";
        for (int i = 0 ; i < params[index_pr].size() ; ++i) {
            out += QString::number(params[index_pr][0]);
            if (i < params[index_pr].size() - 1) {
                out += ",";
            }
        }
        out += ")";
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

void Generator::createLeafRulesSingle(QString primitive_type, QString in, QVector<float> param, QVector3D c, QVector3D rot){

    QString out = primitive_type;
    out += "(";
    for (int i = 0 ; i < param.size() ; ++i) {
        out += QString::number(param[i]);
        if (i < param.size() - 1) {
            out += ",";
        }
    }
    out += ")";
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

    qDebug() << "RULES AVANT : " << rules[in];
    rules.insert(in, {out});
    qDebug() << "RULES APRES : " << rules[in];
}

void Generator::computeSentence() {
    QStringList primitives_str = sentence.split(QRegExp("\\-|\\+|\\*"));
    for (int i = 0 ; i < primitives_str.size() ; ++i) {
        if(!rules.value(primitives_str[i]).isEmpty()){
            sentence.replace(primitives_str[i], rules.value(primitives_str[i])[0]);
        }
    }
}
