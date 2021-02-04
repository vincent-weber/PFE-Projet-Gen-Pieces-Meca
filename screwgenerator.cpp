#include "screwgenerator.h"

ScrewGenerator::ScrewGenerator()
{

}

void ScrewGenerator::createRules() {
    int nb_screw_possibilities = rules.find("Screw")->count();
    unsigned index = std::uniform_int_distribution<int>{0,nb_screw_possibilities-1}(rd);
    QString str = rules.find("Screw")->at(index);
    QStringList primitives_str = str.split(QRegExp("\\-|\\+|\\*"));
    for (int i = 0 ; i < primitives_str.size() ; ++i) {
        generate(primitives_str.at(i));
    }

}

void ScrewGenerator::generate(QString screw_part) {
    if (screw_part == "ScrewHeadCyl") {

        //createLeafRules("cyl", screw_part, /*trucs a generer*/);
    }
    else if (screw_part == "ScrewBody") {

    }
}


