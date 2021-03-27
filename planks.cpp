#include "planks.h"

Planks::Planks()
{
    generator_name = "Planks";
}

void Planks::generateParams(QString planks_part) {
    if (planks_part == "FlatLayout") {
        dist_between_planks = computeParameter(dist_between_planks, rd, 0.18f, 0.6f);
        planks_length = computeParameter(planks_length, rd, 6.0f, 12.0f);
        planks_width = computeParameter(planks_width, rd, 6.0f, 12.0f);
        planks_height = computeParameter(planks_height, rd, 0.6f, 1.2f);
    }
    else if (planks_part == "AllHinges" || planks_part == "RandomHinges") {
        hinge_wing_height = computeParameter(hinge_wing_height, rd, planks_height / 6, planks_height / 4);
        hinge.set_middle_cyl_width(dist_between_planks / 2);
        hinge.set_wing_height(hinge_wing_height);
        hinge.createParams();

        float hinge_length = hinge.get_middle_cyl_height();
        starting_offset = computeParameter(starting_offset, rd, hinge_length*1.5f, hinge_length*2.0f);
        float remaining_space_length = planks_length - starting_offset*2;
        float remaining_space_width = planks_width - starting_offset*2;

        nb_anch_points_length = remaining_space_length / (hinge_length*2.0f);
        float space_for_hinges_length = (nb_anch_points_length-1) * hinge_length;
        float space_for_dist_between_hinges_length = remaining_space_length - space_for_hinges_length;
        dist_between_hinges_length = space_for_dist_between_hinges_length / (nb_anch_points_length-1);

        nb_anch_points_width = remaining_space_width / (hinge_length*2.0f);
        float space_for_hinges_width = (nb_anch_points_width-1) * hinge_length;
        float space_for_dist_between_hinges_width = remaining_space_width - space_for_hinges_width;
        dist_between_hinges_width = space_for_dist_between_hinges_width / (nb_anch_points_width-1);

        screw.set_body_width(hinge.get_hole_radius());
        screw.createParams();

        if (planks_part == "AllHinges") {
            anch_type = PLANKS_ALL_HINGES;
        }
        else if (planks_part == "RandomHinges") {
            anch_type = PLANKS_RANDOM_HINGES;
        }
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
    if (anch_type == PLANKS_ALL_HINGES || anch_type == PLANKS_RANDOM_HINGES) {

        QVector3D coords_anch_point(center[0] + planks_length / 2 - starting_offset, center[1] + planks_height / 2 + hinge_wing_height / 2 - 0.003f, center[2] + planks_width / 2 + dist_between_planks / 2);

        QVector<AnchorPoint> anchor_points_z_pos;
        QVector<AnchorPoint> anchor_points_z_neg;
        QVector3D direction_length(1,0,0);
        for (int i = 0 ; i < nb_anch_points_length ; ++i) {
            AnchorPoint anch_point_z_pos(coords_anch_point, direction_length, dist_between_hinges_length);
            anchor_points_z_pos.push_back(anch_point_z_pos);
            AnchorPoint anch_point_z_neg(QVector3D(coords_anch_point[0], coords_anch_point[1], coords_anch_point[2] - dist_between_planks - planks_width), -direction_length, dist_between_hinges_length);
            anchor_points_z_neg.push_back(anch_point_z_neg);
            coords_anch_point = QVector3D(coords_anch_point[0] - (dist_between_hinges_length + hinge.get_middle_cyl_height()), coords_anch_point[1], coords_anch_point[2]);
        }

        coords_anch_point = QVector3D(center[0] + planks_length / 2 + dist_between_planks / 2, center[1] + planks_height / 2 + hinge_wing_height / 2 - 0.003f, center[2] + planks_width / 2 - starting_offset);

        QVector<AnchorPoint> anchor_points_x_pos;
        QVector<AnchorPoint> anchor_points_x_neg;
        QVector3D direction_width(0,0,-1);
        for (int i = 0 ; i < nb_anch_points_width ; ++i) {
            AnchorPoint anch_point_x_pos(coords_anch_point, direction_width, dist_between_hinges_width);
            anchor_points_x_pos.push_back(anch_point_x_pos);
            AnchorPoint anch_point_x_neg(QVector3D(coords_anch_point[0] - dist_between_planks - planks_length, coords_anch_point[1], coords_anch_point[2]), -direction_width, dist_between_hinges_width);
            anchor_points_z_neg.push_back(anch_point_x_neg);
            coords_anch_point = QVector3D(coords_anch_point[0], coords_anch_point[1], coords_anch_point[2] - (dist_between_hinges_width + hinge.get_middle_cyl_height()));
        }

        anchor_points.push_back(anchor_points_z_pos);
        anchor_points.push_back(anchor_points_z_neg);
        anchor_points.push_back(anchor_points_x_pos);
        anchor_points.push_back(anchor_points_x_neg);
    }
}

void Planks::generateRules(QString planks_part) {
    set_rotation(planks_part);
    if (planks_part == "FlatLayout") {
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
        Parser parser(rule);
        parser.reader();
        base = MechanicalPart(parser.shapes, parser.ops);
    }

    else if (planks_part == "AllHinges" || planks_part == "RandomHinges") {
        QVector<AnchorPoint*> anch_points_chosen = choose_anchor_points();

        QString rule = "";
        for (int i = 0 ; i < anch_points_chosen.size() ; ++i) {
            QString hinge_string = "";
            AnchorPoint* anch_point = anch_points_chosen[i];
            hinge.sentence = hinge.base_sentence;
            hinge.anchor_points.clear();
            hinge.set_prev_anchor_point(anch_point);
            hinge.set_dir_wings();
            hinge.set_center();
            hinge.set_anchor_points();

            for (int k = 0 ; k < hinge.primitives_str.size() ; ++k) {
                hinge.set_rotation(hinge.primitives_str.at(k));
                hinge.generateRules(hinge.primitives_str.at(k));
            }
            hinge.computeSentence();
            rule += hinge.sentence;
            hinge_string += hinge.sentence;

            /*QVector<AnchorPoint*> anch_points_hinge = hinge.choose_anchor_points();
            for (int j = 0 ; j < anch_points_hinge.size() ; ++j) {
                AnchorPoint* anch_p = anch_points_hinge[j];
                screw.sentence = screw.base_sentence;
                screw.set_prev_anchor_point(anch_p);
                screw.set_center();

                for (int k = 0;  k < screw.primitives_str.size() ; ++k) {
                    screw.set_rotation(screw.primitives_str.at(k));
                    screw.generateRules(screw.primitives_str.at(k));
                }
                screw.computeSentence();
                rule += screw.sentence;
                hinge_string += screw.sentence;
                if (i != anch_points_chosen.size()-1) {
                    rule += "+";
                    hinge_string += "+";
                }
            }

            if (i != anch_points_chosen.size()-1) {
                rule += "+";
                hinge_string += "+";
            }*/

            Parser parser(hinge_string);
            parser.reader();
            parts.push_back(MechanicalPart(parser.shapes, parser.ops));
        }
        rules.insert(planks_part, {rule});
        qDebug() << hinge.base_sentence;
    }
}

QVector<AnchorPoint*> Planks::choose_anchor_points() {
    QVector<AnchorPoint*> res;
    if (anch_type == PLANKS_ALL_HINGES) {
        for (int i = 0 ; i < anchor_points.size() ; ++i) {
            for (int j = 0 ; j < anchor_points[i].size() ; ++j) {
                res.push_back(&anchor_points[i][j]);
            }
        }
    }
    else if (anch_type == PLANKS_RANDOM_HINGES) {
        for (int i = 0 ; i < anchor_points.size() ; ++i) {
            for (int j = 0 ; j < anchor_points[i].size() ; ++j) {
                int rand = std::uniform_int_distribution<int>{0,1}(rd);
                if (rand == 0) {
                    res.push_back(&anchor_points[i][j]);
                }
            }
        }
    }
    return res;
}
