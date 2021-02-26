#include "nut.h"

Nut::Nut()
{
    generator_name = "Nut";
}

void Nut::generateParams(QString nut_part) {
    if (nut_part == "NutMainCyl") {
        main_cyl_radius = computeParameter(main_cyl_radius, rd, 1.0f, 3.0f);
        precision_main_cyl = computeParameter(precision_main_cyl, rd, 7, 12);
        if (precision_main_cyl % 2 == 1) ++precision_main_cyl;
        main_cyl_length = computeParameter(main_cyl_length, rd, main_cyl_radius/2, main_cyl_radius);
    }
    else if (nut_part == "NutIntersectCyl") {
        intersect_cyl_radius = computeParameter(intersect_cyl_radius, rd, main_cyl_radius/2, main_cyl_radius*0.9f);
        precision_intersect_cyl = computeParameter(precision_intersect_cyl, rd, 10, 20);
        if (precision_intersect_cyl % 2 == 1) ++precision_intersect_cyl;
    }
}

void Nut::set_center() {

}

void Nut::set_rotation(QString screw_part) {
    rotation = QVector3D(0, PI/2, PI/2);
}

void Nut::set_anchor_points() {

}

void Nut::generateRules(QString nut_part) {
    if (nut_part == "NutMainCyl") {
        createLeafRulesSingle("cyl", nut_part, QVector<float>({main_cyl_radius, main_cyl_length, (float)precision_main_cyl}), center, rotation);
    }
    else if (nut_part == "NutIntersectCyl") {
        createLeafRulesSingle("cyl", nut_part, QVector<float>({intersect_cyl_radius, main_cyl_length, (float)precision_intersect_cyl}), center, rotation);
    }
}

