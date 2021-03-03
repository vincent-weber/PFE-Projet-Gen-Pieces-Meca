#include "generator.h"

QHash<QString, QVector<QString>> Generator::rules;
QHash<QString, QVector<QString>> Generator::base_rules;

void Generator::initRules() {
    rules.insert("Screw", {"ScrewBodyCyl+ScrewHeadCyl", "ScrewBodyCyl+ScrewHeadCyl6", "ScrewBodyCyl+ScrewHeadCub", "ScrewBodyCyl+ScrewHeadCyl6+ScrewInterCyl6"});
    rules.insert("Nut", {"NutMainCyl-NutIntersectCyl"});
    rules.insert("Pipe", {"ClassicCyl"});

    rules.insert("Box", {"BoiteCube", "BoiteRelief"});
    rules.insert("Piston", {"HeadCyl-HeadIntersect+BodyCuboid+EndCyl-EndIntersect"});

    rules.insert("Engine", {"EngineAxis+SeparatorPistons"/*+GroupPistons+SeparatorPistons"*/});
    rules.insert("EngineAxis", {"CylHeadEngine+CylMainAxe+CylExtEngine", "CubHeadEngine+CylMainAxe+CubExtEngine"});
    rules.insert("GroupPistons", {"AlignedPistons4", "AlternatedPistons4"});
    rules.insert("SeparatorPistons", {"CylSeparators", /*"CubSeparators"*/});
    base_rules = rules;
}

QString Generator::recurs(QString in) {
    QString out = in;
    QStringList split_entries = in.split(QRegExp("\\-|\\+|\\*"));
    bool changed = false;
    for (int i = 0 ; i < split_entries.size() ; ++i) {
        bool exists = base_rules.keys().contains(split_entries.at(i));
        if (exists) {
            QString key = split_entries.at(i);
            int nb_possibilities = base_rules.find(key)->count();
            unsigned index = std::uniform_int_distribution<int>{0,nb_possibilities-1}(rd_gen);
            out.replace(split_entries.at(i), base_rules.find(key)->at(index));
            changed = true;
        }
    }
    if (changed) {
        out = recurs(out);
    }
    return out;
}

void Generator::createParams() {
    int nb_part_possibilities = rules.find(generator_name)->count();
    unsigned index = std::uniform_int_distribution<int>{0,nb_part_possibilities-1}(rd_gen);
    base_sentence = rules.find(generator_name)->at(index);
    qDebug() << "BASE SENTENCE AVANT : " << base_sentence;
    base_sentence = recurs(base_sentence);
    qDebug() << "BASE SENTENCE APRES : " << base_sentence;
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

void Generator::set_prev_anchor_point(AnchorPoint* anchor_point) {
    anchor_point_prev_lvl = anchor_point;
    direction = anchor_point->direction;
}

float Generator::get_max_possible_size() {
    float max_value = max_size;
    if (anchor_point_prev_lvl != nullptr) {
        float max_accepted_size = anchor_point_prev_lvl->max_accepted_size;
        if (max_accepted_size < max_value) {
            max_value = max_accepted_size;
        }
    }
    return max_value;
}

QString Generator::createLeafRulesMultiple(QVector<QString>& primitives, QString op_bools, QVector<QVector<float>>& params, QVector<QVector3D>& centers, QVector<QVector3D>& rots) {
    QString out = "";
    int size = primitives.size();
    for (int index_pr = 0 ; index_pr < size ; ++index_pr) {
        //changer params en Qvector<Qvector<float>> dans le cas ou on a plusieurs paramètres ?
        out += primitives[index_pr];
        out += "(";
        for (int i = 0 ; i < params[index_pr].size() ; ++i) {
            out += QString::number(params[index_pr][i]);
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

//    qDebug() << "RULES AVANT : " << rules[in];
    rules.insert(in, {out});
//    qDebug() << "RULES APRES : " << rules[in];
}

void Generator::computeSentence() {
    QStringList primitives_str = sentence.split(QRegExp("\\-|\\+|\\*"));
    for (int i = 0 ; i < primitives_str.size() ; ++i) {
        if(!rules.value(primitives_str[i]).isEmpty()){
            sentence.replace(primitives_str[i], rules.value(primitives_str[i])[0]);
        }
    }
}
