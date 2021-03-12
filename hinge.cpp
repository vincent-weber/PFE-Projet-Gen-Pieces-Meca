#include "hinge.h"

Hinge::Hinge()
{
    generator_name = "Hinge";
    max_size = 1.8f;
    min_size = 0.6f;
}

void Hinge::generateParams(QString hinge_part) {
    float max_value = get_max_possible_size();
    float min_value = min_size;
    if (max_value < min_value) {
        max_value = min_value;
    }

    /*rules.insert("HingeWings", {"AlignedSquared", "AlignedRounded", "PerpendicularSquared", "PerpendicularRounded"});
    rules.insert("HingeHolePattern", {"Random4", "RandomN", "Angles", "3x3Grid"});*/

    if (hinge_part == "HingeMiddleCyl") {
        middle_cyl_length = computeParameter(middle_cyl_length, rd, min_value, max_value);
        middle_cyl_width = computeParameter(middle_cyl_width, rd, middle_cyl_length*0.1f, middle_cyl_length*0.2f);
        middle_cyl_precision = computeParameter(middle_cyl_precision, rd, 10, 20);

    }
    else if (hinge_part == "AlignedSquared" || hinge_part == "AlignedRounded" || hinge_part == "PerpendicularSquared" || hinge_part == "PerpendicularRounded" ) {
        wing_height = computeParameter(wing_height, rd, middle_cyl_width*0.2f, middle_cyl_width*0.75f);
        wing_length = computeParameter(wing_length, rd, middle_cyl_width*4, middle_cyl_width*8);
        wing_width = computeParameter(wing_width, rd, middle_cyl_length*0.95f, middle_cyl_length);
    }


}

void Hinge::set_center() {
    center = QVector3D(0,0,0);
}

void Hinge::set_rotation(QString hinge_part) {
    rotation = QVector3D(0,0,0);
}

void Hinge::set_anchor_points() {

}

QVector<AnchorPoint*> Hinge::choose_anchor_points() {

}

void Hinge::generateRules(QString hinge_part) {
    //TEMP
    direction = QVector3D(1,0,0);
    if (hinge_part == "HingeMiddleCyl") {
        createLeafRulesSingle("cyl", hinge_part, {middle_cyl_width, middle_cyl_length, (float)middle_cyl_precision}, center, rotation);
    }
    else if (hinge_part == "AlignedSquared") {
        QVector3D center_cub_1(center[0] + (- middle_cyl_width - wing_length/2 + 0.003f) * direction[0], center[1] + (- middle_cyl_width - wing_length/2 + 0.003f) * direction[1], center[2] + (- middle_cyl_width - wing_length/2 + 0.003f) * direction[2]);
        QVector3D center_cub_2(center[0] + (middle_cyl_width + wing_length/2 - 0.003f) * direction[0], center[1] + (middle_cyl_width + wing_length/2 - 0.003f) * direction[1], center[2] + (middle_cyl_width + wing_length/2 - 0.003f) * direction[2]);

        QVector<QString> primitives({"cub", "cub"});
        QVector<QVector3D> centers({center_cub_1, center_cub_2});
        QVector<QVector3D> rots({rotation, rotation});
        QVector<QVector<float>> params{{wing_length, wing_height, wing_width},{wing_length, wing_height, wing_width}};
        QString rule = createLeafRulesMultiple(primitives, "+", params, centers, rots);
        rules.insert(hinge_part, {rule});
    }
    else if (hinge_part == "AlignedRounded") {
        QVector3D center_cub_1(center[0] + (- middle_cyl_width - wing_length/2 + 0.003f) * direction[0], center[1] + (- middle_cyl_width - wing_length/2 + 0.003f) * direction[1], center[2] + (- middle_cyl_width - wing_length/2 + 0.003f) * direction[2]);
        QVector3D center_cub_2(center[0] + (middle_cyl_width + wing_length/2 - 0.003f) * direction[0], center[1] + (middle_cyl_width + wing_length/2 - 0.003f) * direction[1], center[2] + (middle_cyl_width + wing_length/2 - 0.003f) * direction[2]);
        QVector3D center_cyl_1(center[0] - middle_cyl_width * direction[0], center[1] - middle_cyl_width * direction[1], center[2] - middle_cyl_width * direction[2]);
        QVector3D center_cyl_2(center[0] + middle_cyl_width * direction[0], center[1] + middle_cyl_width * direction[1], center[2] + middle_cyl_width * direction[2]);

        QVector<QString> primitives({"cub", "cyl", "cub", "cyl"});
        QVector<QVector3D> centers({center_cub_1, center_cyl_1, center_cub_2, center_cyl_2});
        QVector<QVector3D> rots({rotation, QVector3D(PI/2,0,0), rotation, QVector3D(PI/2,0,0)});
        QVector<QVector<float>> params{{wing_length, wing_height, wing_width}, {wing_width*0.6f, wing_height*2, 32}, {wing_length, wing_height, wing_width}, {wing_width*0.6f, wing_height*2, 32}};
        QString rule = createLeafRulesMultiple(primitives, "/+/", params, centers, rots);
        rules.insert(hinge_part, {rule});
    }
}
