#include "planks.h"

Planks::Planks()
{
    generator_name = "Planks";
}


void Planks::generateParams(QString planks_part) {
    if (planks_part == "5PlanksFlat") {
        dist_between_planks = computeParameter(dist_between_planks, rd, 0.18f, 0.6f);
        planks_length = computeParameter(planks_length, rd, 6.0f, 12.0f);
        planks_width = computeParameter(planks_width, rd, 6.0f, 12.0f);
        planks_height = computeParameter(planks_height, rd, 0.6f, 1.2f);
    }

}

void Planks::set_center() {
    center = QVector3D(0,0,0);
}

void Planks::set_rotation(QString planks_part) {
    rotation = QVector3D(0,0,0);
    if (planks_part == "5PlanksFlat") {
        rotation = QVector3D(0,0,0);
    }
}

void Planks::set_anchor_points() {

}

QVector<AnchorPoint*> Planks::choose_anchor_points() {

}

void Planks::generateRules(QString planks_part) {
    set_rotation(planks_part);
    if (planks_part == "5PlanksFlat") {
        QVector3D center_plank_center(center);
        QVector3D center_plank_x_neg(center[0] - planks_length - dist_between_planks, center[1], center[2]);
        QVector3D center_plank_x_pos(center[0] + planks_length + dist_between_planks, center[1], center[2]);
        QVector3D center_plank_z_neg(center[0], center[1], center[2] - planks_width - dist_between_planks);
        QVector3D center_plank_z_pos(center[0], center[1], center[2] + planks_width + dist_between_planks);

        QVector<QString> primitives = {"cub", "cub", "cub", "cub", "cub"};
        QString op_bool = "++++";
        QVector<QVector<float>> params(5, {planks_length, planks_height, planks_width});
        QVector<QVector3D> centers = {center_plank_center, center_plank_x_neg, center_plank_x_pos, center_plank_z_neg, center_plank_z_pos};
        QVector<QVector3D> rots(5, rotation);
        QString rule = createLeafRulesMultiple(primitives, op_bool, params, centers, rots);

        rules.insert(planks_part, {rule});
    }
}
