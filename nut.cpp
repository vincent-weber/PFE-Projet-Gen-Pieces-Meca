#include "nut.h"

Nut::Nut()
{
    generator_name = "Nut";
}

void Nut::generateParams(QString nut_part) {
    float max_value = get_max_possible_size();
    qDebug() << max_value << "LA VALEUR MAX";

    if (nut_part == "NutMainCyl") {
        main_cyl_radius = computeParameter(main_cyl_radius, rd, 1.0f, max_value);
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
    QVector3D offset = - anchor_point_prev_lvl->direction*0.001;
    center = QVector3D(anchor_point_prev_lvl->coords - anchor_point_prev_lvl->direction*(main_cyl_length) + offset);
}

void Nut::set_rotation(QString screw_part) {
    QVector3D vec_un(1,1,1);
    QVector3D vec_base;

    if (screw_part == "NutMainCyl") {
        vec_base= QVector3D(0,0,1);
    }
    else if (screw_part == "NutIntersectCyl") {
        vec_base= QVector3D(0,0,1);
    }

    if(vec_base == direction || vec_base == -direction) {
        rotation = QVector3D(0,0,0);
    }
    else rotation = (vec_un - (vec_base + direction)) * PI/2;
}

void Nut::set_anchor_points() {
    //Juste celui au centre de l'ecrou.
    QVector<AnchorPoint> anchor;
    AnchorPoint anch(center, -direction, intersect_cyl_radius);
    anchor.push_back(anch);
    anchor_points.push_back(anchor);
}

QVector<AnchorPoint> Nut::choose_anchor_points() {
}

void Nut::generateRules(QString nut_part) {
    if (nut_part == "NutMainCyl") {
        createLeafRulesSingle("cyl", nut_part, QVector<float>({main_cyl_radius, main_cyl_length, (float)precision_main_cyl}), center, rotation);
    }
    else if (nut_part == "NutIntersectCyl") {
        createLeafRulesSingle("cyl", nut_part, QVector<float>({intersect_cyl_radius, main_cyl_length, (float)precision_intersect_cyl}), center, rotation);
    }
}

