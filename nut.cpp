#include "nut.h"

Nut::Nut()
{
    generator_name = "Nut";
}

void Nut::generate(QString nut_part) {
    if (nut_part == "NutMainCyl") {
        main_cyl_radius = computeParameter(main_cyl_radius, rd, 1.0f, 3.0f);
        int precision  = std::uniform_real_distribution<float>{7,12}(rd);
        if (precision % 2 == 1) ++precision;
        main_cyl_length = computeParameter(main_cyl_length, rd, main_cyl_radius/2, main_cyl_radius);
        createLeafRulesSingle("cyl", nut_part, QVector3D(main_cyl_radius, main_cyl_length, precision), QVector3D(0,0,0), QVector3D(PI/2,PI/2,0));
    }
    else if (nut_part == "NutIntersectCyl") {
        float intersect_cyl_radius = std::uniform_real_distribution<float>{main_cyl_radius/2, main_cyl_radius*0.9f}(rd);
        int precision = std::uniform_real_distribution<float>{10,20}(rd);
        if (precision % 2 == 1) ++precision;
        float intersect_cyl_length = main_cyl_length;
        createLeafRulesSingle("cyl", nut_part, QVector3D(intersect_cyl_radius, intersect_cyl_length, precision), QVector3D(0,0,0), QVector3D(PI/2,PI/2,0));
    }
}
