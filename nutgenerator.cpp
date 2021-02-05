#include "nutgenerator.h"

NutGenerator::NutGenerator()
{
    generator_name = "Nut";
}

void NutGenerator::generate(QString nut_part) {
    if (nut_part == "NutMainCyl") {
        main_cyl_radius = std::uniform_real_distribution<float>{1,3}(rd);
        int precision  = std::uniform_real_distribution<float>{7,12}(rd);
        if (precision % 2 == 1) ++precision;
        main_cyl_length = std::uniform_real_distribution<float>{main_cyl_radius/2, main_cyl_radius}(rd);
        createLeafRules("cyl", nut_part, QVector3D(main_cyl_radius, main_cyl_length, precision), QVector3D(0,0,0), QVector3D(PI/2,PI/2,0));
    }
    else if (nut_part == "NutIntersectCyl") {
        float intersect_cyl_radius = std::uniform_real_distribution<float>{main_cyl_radius/2, main_cyl_radius*0.9f}(rd);
        int precision = std::uniform_real_distribution<float>{10,20}(rd);
        if (precision % 2 == 1) ++precision;
        float intersect_cyl_length = main_cyl_length;
        createLeafRules("cyl", nut_part, QVector3D(intersect_cyl_radius, intersect_cyl_length, precision), QVector3D(0,0,0), QVector3D(PI/2,PI/2,0));
    }
}
