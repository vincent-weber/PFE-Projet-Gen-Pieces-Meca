#include "hinge.h"

Hinge::Hinge()
{
    generator_name = "Hinge";
    center = QVector3D(0,0,0);
    max_size = 1.0f;
    min_size = 0.5f;
}

void Hinge::generateParams(QString hinge_part) {
    float max_value = get_max_possible_size();
    float min_value = min_size;
    if (max_value < min_value) {
        max_value = min_value;
    }

    //rules.insert("HingeWings", {"AlignedSquared", "AlignedRounded", "PerpendicularSquared", "PerpendicularRounded"});

    if (hinge_part == "HingeMiddleCyl") {
        middle_cyl_length = computeParameter(middle_cyl_length, rd, min_value, max_value);
        middle_cyl_width = computeParameter(middle_cyl_width, rd, middle_cyl_length*0.1f, middle_cyl_length*0.2f);
        middle_cyl_precision = computeParameter(middle_cyl_precision, rd, 10, 20);

    }
    else if (hinge_part == "AlignedSquared" || hinge_part == "AlignedRounded" || hinge_part == "PerpendicularSquared" || hinge_part == "PerpendicularRounded") {
        wing_height = computeParameter(wing_height, rd, middle_cyl_width*0.2f, middle_cyl_width*0.75f);
        wing_length = computeParameter(wing_length, rd, middle_cyl_width*4, middle_cyl_width*6);
        wing_width = computeParameter(wing_width, rd, middle_cyl_length*0.95f, middle_cyl_length);

        if (hinge_part == "AlignedRounded" || hinge_part == "PerpendicularRounded") {
            is_rounded = true;
            rounding_cyl_width = wing_length;
            rounding_cyl_height = wing_height*2;
            rounding_cyl_precision = 32;
        }
    }

    //rules.insert("HingeHolePattern", {"Random4Max", "RandomN", "Angles", "3x3Grid"});
    else if (hinge_part == "Random4Max" || hinge_part == "RandomN" || hinge_part == "Angles" || hinge_part == "3x3Grid") {
        float min_dim = min(wing_length, wing_width);
        hole_radius = computeParameter(hole_radius, rd, min_dim / 20, min_dim / 10);
        if (hinge_part == "Random4Max") {
            nb_holes = 4;
            anch_type = HINGE_RANDOM;
        }
    }
}

void Hinge::set_dir_wings() {
    if (direction == QVector3D(1,0,0)) {
        dir_wings = QVector3D(0,0,1);
    }
    else if (direction == QVector3D(-1,0,0)) {
        dir_wings = QVector3D(0,0,-1);
    }
    else if (direction == QVector3D(0,0,1)) {
        dir_wings = QVector3D(1,0,0);
    }
    else if (direction == QVector3D(0,0,-1)) {
        dir_wings = QVector3D(-1,0,0);
    }
}

void Hinge::set_center() {
    center = anchor_point_prev_lvl->coords;
}

void Hinge::set_rotation(QString hinge_part) {
    if (anchor_point_prev_lvl == nullptr) {
        rotation = QVector3D(0,0,0);
        return;
    }

    if (hinge_part == "HingeMiddleCyl") {
        if (direction == QVector3D(1,0,0) || direction == QVector3D(-1,0,0)) {
            rotation = QVector3D(0, PI/2, 0);
        }
        else {
            rotation = QVector3D(0,0,0);
        }
    }
    else if (hinge_part == "AlignedSquared" || hinge_part == "AlignedRounded") {
        if (direction == QVector3D(1,0,0) || direction == QVector3D(-1,0,0)) {
            rotation = QVector3D(0, PI/2, 0);
        }
        else {
            rotation = QVector3D(0,0,0);
        }
    }
}

void Hinge::set_anchor_points() {
    if (anch_type == HINGE_RANDOM) {
        QVector<AnchorPoint>  anch_p;
        float max_x = 0, min_x = 0, max_z = 0, min_z = 0;
        if (dir_wings == QVector3D(0,0,1)) {
            max_z = center[2] + middle_cyl_width + wing_length - hole_radius;
            min_z = center[2] + middle_cyl_width + hole_radius;
            max_x = center[0] + wing_width/2 - hole_radius;
            min_x = center[0] - wing_width/2 + hole_radius;
        }
        else if (dir_wings == QVector3D(0,0,-1)) {
            max_z = center[2] - (middle_cyl_width + wing_length - hole_radius);
            min_z = center[2] - (middle_cyl_width + hole_radius);
            max_x = center[0] - (wing_width/2 - hole_radius);
            min_x = center[0] - (-wing_width/2 + hole_radius);
        }
        else if (dir_wings == QVector3D(1,0,0)) {
            max_x = center[0] + middle_cyl_width + wing_length - hole_radius;
            min_x = center[0] + middle_cyl_width + hole_radius;
            max_z = center[2] + wing_width/2 - hole_radius;
            min_z = center[2] - wing_width/2 + hole_radius;
        }
        else if (dir_wings == QVector3D(-1,0,0)) {
            max_x = center[0] - (middle_cyl_width + wing_length - hole_radius);
            min_x = center[0] - (middle_cyl_width + hole_radius);
            max_z = center[2] - (wing_width/2 - hole_radius);
            min_z = center[2] - (-wing_width/2 + hole_radius);
        }
            /*if (dir_wings == QVector3D(0,0,1)) {
                max_z = center[2] + middle_cyl_width + wing_length - hole_radius - rounding_cyl_width;
                min_z = center[2] + middle_cyl_width + hole_radius;
                max_x = center[0] + wing_width/2 - hole_radius;
                min_x = center[0] - wing_width/2 + hole_radius;
            }
            else if (dir_wings == QVector3D(0,0,-1)) {
                max_z = center[2] - (middle_cyl_width + wing_length - hole_radius - rounding_cyl_width);
                min_z = center[2] - (middle_cyl_width + hole_radius);
                max_x = center[0] - (wing_width/2 - hole_radius);
                min_x = center[0] - (-wing_width/2 + hole_radius);
            }
            else if (dir_wings == QVector3D(1,0,0)) {
                max_x = center[0] + middle_cyl_width + wing_length - hole_radius - rounding_cyl_width;
                min_x = center[0] + middle_cyl_width + hole_radius;
                max_z = center[2] + wing_width/2 - hole_radius;
                min_z = center[2] - wing_width/2 + hole_radius;
            }
            else if (dir_wings == QVector3D(-1,0,0)) {
                max_x = center[0] - (middle_cyl_width + wing_length - hole_radius - rounding_cyl_width);
                min_x = center[0] - (middle_cyl_width + hole_radius);
                max_z = center[2] - (wing_width/2 - hole_radius);
                min_z = center[2] - (-wing_width/2 + hole_radius);
            }*/
        if (min_x > max_x) min_x = max_x;
        if (min_z > max_z) min_z = max_z;
        QVector<QVector3D> holes;
        for (unsigned i = 0 ; i < nb_holes ; ++i) {
            QVector3D coords;
            unsigned max_nb_tries = 100;
            unsigned nb_tries = 0;
            bool limit_reached = false;
            bool is_ok = true;
            do {
                ++nb_tries;
                if (nb_tries == max_nb_tries) {
                    limit_reached = true;
                    break;
                }

                qDebug() << "HOLE COUNT : " << holes.size();
                qDebug() << "MIN X : " << min_x;
                qDebug() << "MAX X : " << max_x;
                qDebug() << "MIN Z : " << min_z;
                qDebug() << "MAX Z : " << max_z;
                float x = std::uniform_real_distribution<float>{min_x, max_x}(rd);
                float z = std::uniform_real_distribution<float>{min_z, max_z}(rd);
                coords = QVector3D(x, center[1], z);
                is_ok = true;
                for (QVector3D& hole_coord : holes) {
                    float dist = coords.distanceToPoint(hole_coord);
                    if (dist < hole_radius*2) {
                        is_ok = false;
                        break;
                    }
                    else if (is_rounded) {
                        //limites tres approximatives
                        float limit_value = min(wing_width*0.25f, rounding_cyl_width - hole_radius*4);
                        if (coords.distanceToPoint(center) > limit_value) {
                            is_ok = false;
                            break;
                        }
                    }
                }

            } while(!is_ok);
            if (!limit_reached) {
                holes.push_back(coords);
                anch_p.push_back(AnchorPoint(coords, QVector3D(0,-1,0), hole_radius));
                if (dir_wings == QVector3D(1,0,0)) {
                    anch_p.push_back(AnchorPoint(QVector3D(center[0] - (coords[0] - center[0]), coords[1], coords[2]), QVector3D(0,-1,0), hole_radius));
                }
                else if (dir_wings == QVector3D(-1,0,0)) {
                    anch_p.push_back(AnchorPoint(QVector3D(center[0] + (coords[0] - center[0]), coords[1], coords[2]), QVector3D(0,-1,0), hole_radius));
                }
                else if (dir_wings == QVector3D(0,0,1)) {
                    anch_p.push_back(AnchorPoint(QVector3D(coords[0], coords[1], center[2] - (coords[2] - center[2])), QVector3D(0,-1,0), hole_radius));
                }
                else if (dir_wings == QVector3D(0,0,-1)) {
                    anch_p.push_back(AnchorPoint(QVector3D(coords[0], coords[1], center[2] + (coords[2] - center[2])), QVector3D(0,-1,0), hole_radius));
                }
                //anch_p.push_back(AnchorPoint)
            }
        }
        anchor_points.push_back(anch_p);
    }
}

QVector<AnchorPoint*> Hinge::choose_anchor_points() {
    QVector<AnchorPoint*> res;
    if (anch_type == HINGE_RANDOM) {
        for (int i = 0 ; i < anchor_points[0].size() ; ++i) {
            res.push_back(&anchor_points[0][i]);
        }
        return res;
    }
}

void Hinge::generateRules(QString hinge_part) {
    set_rotation(hinge_part);
    if (hinge_part == "HingeMiddleCyl") {
        createLeafRulesSingle("cyl", hinge_part, {middle_cyl_width, middle_cyl_length, (float)middle_cyl_precision}, center, rotation);
    }
    else if (hinge_part == "AlignedSquared") {
        QVector3D center_cub_1(center[0] + (- middle_cyl_width - wing_length/2 + wing_length*0.005f) * dir_wings[0], center[1] + (- middle_cyl_width - wing_length/2 + wing_length*0.005f) * dir_wings[1], center[2] + (- middle_cyl_width - wing_length/2 + wing_length*0.005f) * dir_wings[2]);
        QVector3D center_cub_2(center[0] + (middle_cyl_width + wing_length/2 - wing_length*0.005f) * dir_wings[0], center[1] + (middle_cyl_width + wing_length/2 - wing_length*0.005f) * dir_wings[1], center[2] + (middle_cyl_width + wing_length/2 - wing_length*0.005f) * dir_wings[2]);

        QVector<QString> primitives({"cub", "cub"});
        QVector<QVector3D> centers({center_cub_1, center_cub_2});
        QVector<QVector3D> rots({rotation, rotation});
        QVector<QVector<float>> params{{wing_length, wing_height, wing_width},{wing_length, wing_height, wing_width}};
        QString rule = createLeafRulesMultiple(primitives, "+", params, centers, rots);
        rules.insert(hinge_part, {rule});
    }
    else if (hinge_part == "AlignedRounded") {
        QVector3D center_cub_1(center[0] + (- middle_cyl_width - wing_length/2 + wing_length*0.005f) * dir_wings[0], center[1] + (- middle_cyl_width - wing_length/2 + wing_length*0.005f) * dir_wings[1], center[2] + (- middle_cyl_width - wing_length/2 + wing_length*0.005f) * dir_wings[2]);
        QVector3D center_cub_2(center[0] + (middle_cyl_width + wing_length/2 - wing_length*0.005f) * dir_wings[0], center[1] + (middle_cyl_width + wing_length/2 - wing_length*0.005f) * dir_wings[1], center[2] + (middle_cyl_width + wing_length/2 - wing_length*0.005f) * dir_wings[2]);
        //QVector3D center_cyl_1(center[0] - middle_cyl_width * dir_wings[0], center[1] - middle_cyl_width * dir_wings[1], center[2] - middle_cyl_width * dir_wings[2]);
        //QVector3D center_cyl_2(center[0] + middle_cyl_width * dir_wings[0], center[1] + middle_cyl_width * dir_wings[1], center[2] + middle_cyl_width * dir_wings[2]);
        QVector3D center_round_cyl = center;

        QVector<QString> primitives({"cub", "cyl", "cub", "cyl"});
        QVector<QVector3D> centers({center_cub_1, center_round_cyl, center_cub_2, center_round_cyl});
        QVector<QVector3D> rots({rotation, QVector3D(PI/2,0,0), rotation, QVector3D(PI/2,0,0)});
        QVector<QVector<float>> params{{wing_length, wing_height, wing_width}, {rounding_cyl_width, rounding_cyl_height, rounding_cyl_precision}, {wing_length, wing_height, wing_width}, {rounding_cyl_width, rounding_cyl_height, rounding_cyl_precision}};
        QString rule = createLeafRulesMultiple(primitives, "/+/", params, centers, rots);
        rules.insert(hinge_part, {rule});
    }
    else if (hinge_part == "Random4Max") {
        if (anchor_points[0].size() == 0) {
            qDebug() << "PB : SET ANCHOR POINTS PAS APPELE OU BUGGE";
        }

        QVector<QString> primitives;
        QVector<QVector3D> centers;
        QVector<QVector3D> rots;
        QVector<QVector<float>> params;
        QString op_bools;

        for (int i = 0 ; i < anchor_points[0].size() ; ++i) {
            primitives.push_back("cyl");
            centers.push_back(anchor_points[0][i].coords);
            rots.push_back(QVector3D(PI/2,0,0));
            params.push_back({hole_radius, wing_height*2.0f, 32});
            op_bools += "-";
        }

        QString rule = createLeafRulesMultiple(primitives, op_bools, params, centers, rots);
        rules.insert(hinge_part, {rule});
    }
}
