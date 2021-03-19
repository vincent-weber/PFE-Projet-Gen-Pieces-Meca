#include "box.h"

Box::Box()
{
    generator_name = "Box";
    max_size = 10;
    min_size = 2.5f;
    center = QVector3D(0,0,0);
    rotation = QVector3D(0,0,0);
}

//"Simple3x3Rand", "Simple3x3Sym" "Relief3x3Rand", "Relief3x3Sym", "LongOneFace"

void Box::generateParams(QString box_part) {
    if (box_part == "Simple3x3Rand" || box_part == "Simple3x3Sym" || box_part == "SimpleAngles" || box_part == "SimpleEdge") {
        float max_value = get_max_possible_size();
        float min_value = min_size;
        if (max_value < min_value) min_value = max_value;

        box_height = computeParameter(box_height, rd, min_value, max_value);
        box_width = computeParameter(box_width, rd, min_value, max_value);
        box_length = computeParameter(box_length, rd, min_value, max_value);
    }

    else if (box_part == "Relief3x3Rand" || box_part == "Relief3x3Sym" || box_part == "ReliefAngles" || box_part == "ReliefEdge") {
        float max_value = get_max_possible_size();
        float min_value = min_size;
        if (max_value < min_value) min_value = max_value;
        box_height = computeParameter(box_height, rd, min_value, max_value);
        box_width = computeParameter(box_width, rd, min_value, max_value);
        box_length = computeParameter(box_length, rd, min_value, max_value);

        float min_param = min(box_height, box_width);
        min_param = min(min_param, box_length);

        box_thickness = min_param / 16;
    }

    else if (box_part == "LongOneFace") {
        box_length = computeParameter(box_length, rd, 7.5f, 30.0f);
        box_width = computeParameter(box_width, rd, box_length * 0.075, box_length * 0.15f);
        box_height = computeParameter(box_height, rd, box_length * 0.075, box_length * 0.15f);

    }

    if (anch_type == UNDEFINED) {
        if (box_part == "Simple3x3Rand" || box_part == "Relief3x3Rand") {
            anch_type = BOX_GRID_3X3_RANDOM;
        }
        else if (box_part == "Simple3x3Sym" || box_part == "Relief3x3Sym") {
            anch_type = BOX_GRID_3X3_SYMMETRIC;
        }
        else if (box_part == "LongOneFace") {
            anch_type = BOX_ONE_FACE_ALIGNED;
        }
        else if(box_part == "SimpleAngles" || box_part == "ReliefAngles"){
            anch_type = BOX_ANGLES;
        }
        else if(box_part == "SimpleEdge" || box_part == "ReliefEdge"){
            anch_type = BOX_EDGE;
        }
    }
}

void Box::set_anchor_points() {
    //TODO : check la distance avec le point d'ancrage précédent pour ne pas l'ajouter à cet objet
    //génération de points d'ancrage par grille de 3x3, peut etre faire une autre méthode (aléatoire)

    if (anch_type == BOX_GRID_3X3_SYMMETRIC || anch_type == BOX_GRID_3X3_RANDOM) {
        //haut et bas de la boite
        float offset_x = box_length/4;
        float offset_z = box_width/4;
        float y = center.y() + box_height/2;
        float x = center.x() + offset_x;
        float z = center.z() + offset_z;

        float max_accepted_size_anchor_point = min(box_length/4, box_width/4);
        QVector<AnchorPoint> anchor_face1;
        QVector<AnchorPoint> anchor_face2;
        for (int i = 0 ; i < 3 ; ++i) {
            for (int j = 0 ; j < 3 ; ++j) {
                QVector3D coords(x,y,z);
                QVector3D coords2(x,y-box_height,z);
                QVector3D direction(0,1,0);
                AnchorPoint anch(coords, direction, max_accepted_size_anchor_point);
                anch.owner_object = this;
                AnchorPoint anch2(coords2, -direction, max_accepted_size_anchor_point);
                anchor_face1.push_back(anch);
                anchor_face2.push_back(anch2);
                x -= offset_x;
            }
            x = center.x() + offset_x;
            z -= offset_z;

        }
        anchor_points.push_back(anchor_face1);
        anchor_points.push_back(anchor_face2);

        //fond et devant de la boite
        offset_x = box_length/4;
        float offset_y = box_height/4;
        z = center.z() + box_width/2;
        x = center.x() + offset_x;
        y = center.y() + offset_y;

        QVector<AnchorPoint> anchor_face3;
        QVector<AnchorPoint> anchor_face4;
        max_accepted_size_anchor_point = min(box_length/4, box_height/4);
        for (int i = 0 ; i < 3 ; ++i) {
            for (int j = 0 ; j < 3 ; ++j) {
                QVector3D coords(x,y,z);
                QVector3D coords2(x,y,z-box_width);
                QVector3D direction(0,0,1);
                AnchorPoint anch(coords, direction, max_accepted_size_anchor_point);
                AnchorPoint anch2(coords2, -direction, max_accepted_size_anchor_point);
                anchor_face3.push_back(anch);
                anchor_face4.push_back(anch2);
                x -= offset_x;
            }
            x = center.x() + offset_x;
            y -= offset_y;
        }
        anchor_points.push_back(anchor_face3);
        anchor_points.push_back(anchor_face4);

        //gauche et droite de la boite
        offset_y = box_height/4;
        offset_z = box_width/4;
        x = center.x() + box_length/2;
        y = center.y() + offset_y;
        z = center.z() + offset_z;

        QVector<AnchorPoint> anchor_face5;
        QVector<AnchorPoint> anchor_face6;
        max_accepted_size_anchor_point = min(box_width/4, box_height/4);
        for (int i = 0 ; i < 3 ; ++i) {
            for (int j = 0 ; j < 3 ; ++j) {
                QVector3D coords(x,y,z);
                QVector3D coords2(x-box_length,y,z);
                QVector3D direction(1,0,0);
                AnchorPoint anch(coords, direction, max_accepted_size_anchor_point);
                AnchorPoint anch2(coords2, -direction, max_accepted_size_anchor_point);
                anchor_face5.push_back(anch);
                anchor_face6.push_back(anch2);
                z -= offset_z;
            }
            z = center.z() + offset_z;
            y -= offset_y;
        }
        anchor_points.push_back(anchor_face5);
        anchor_points.push_back(anchor_face6);
    }
    else if (anch_type == BOX_ONE_FACE_ALIGNED) {
        QVector<AnchorPoint> anch_points;
        float nb_anch_points = box_length / 2.0f - 1;
        float offset = box_length / (nb_anch_points + 1);
        QVector3D coords (center[0] - box_length/2.0f + 2.0f, center[1], center[2] + box_width/2.0f);
        QVector3D direction_anch_p(0,0,1);

        for (int i = 0 ; i < nb_anch_points ; ++i) {
            AnchorPoint anch_p(coords, direction_anch_p, offset);
            coords = QVector3D(coords[0] + offset, coords[1], coords[2]);
            anch_points.push_back(anch_p);
        }
        anchor_points.push_back(anch_points);
    }
    else if (anch_type == BOX_ANGLES){
        //Place des points d'encrage a chaque. //x : length, y = height, z = width;
        //haut et bas de la boite
        float y = center.y() + box_height/2; //FIXE
        float x = center.x() + box_length/2;
        float z = center.z() + box_width/2;

        float max_accepted_size_anchor_point = min(box_length/8, box_width/8);

        float x_offset = max_accepted_size_anchor_point;
        float z_offset = max_accepted_size_anchor_point;
        QVector<AnchorPoint> anchor_face1;
        QVector<AnchorPoint> anchor_face2;
        for (int i = 0 ; i < 2 ; ++i) {
            for (int j = 0 ; j < 2 ; ++j) {
                QVector3D coords(x-x_offset,y,z-z_offset);
                QVector3D coords2(x-x_offset,y-box_height,z-z_offset);
                QVector3D direction(0,1,0);
                AnchorPoint anch(coords, direction, max_accepted_size_anchor_point);
                anch.owner_object = this;
                AnchorPoint anch2(coords2, -direction, max_accepted_size_anchor_point);
                anchor_face1.push_back(anch);
                anchor_face2.push_back(anch2);
                x = -x; x_offset = -x_offset;
            }
            z = -z; z_offset = -z_offset;
        }
        anchor_points.push_back(anchor_face1);
        anchor_points.push_back(anchor_face2);
    }

    else if(anch_type == BOX_EDGE){
        float z = center.z() + box_width/2; //FIXE
        float x = center.x() + box_length/2; //FIXE SI i = 1
        float y = center.y() + box_height/2;



        float max_accepted_size_anchor_point = min(box_length/15, box_height/15);
        float y_offset = max_accepted_size_anchor_point*4;
        float x_offset = max_accepted_size_anchor_point;

        int screwNum = box_height/y_offset;
        qDebug() << "Nombre de vis" << screwNum;

        QVector<AnchorPoint> anchor_face;
        //        QVector<AnchorPoint> anchor_face4;
        for (int i = 0 ; i < 1 ; ++i) {
            for (int j = 0 ; j < screwNum ; ++j) {
                QVector3D coords(x-x_offset,y-y_offset,z);
                //                QVector3D coords2(x,y,z-box_width);
                QVector3D direction(0,0,1);
                AnchorPoint anch(coords, direction, max_accepted_size_anchor_point);
                //                AnchorPoint anch2(coords2, -direction, max_accepted_size_anchor_point);
                anchor_face.push_back(anch);
                //                anchor_face4.push_back(anch2);
                y -= y_offset;
            }
        }
        anchor_points.push_back(anchor_face);
    }
}

QVector<AnchorPoint*> Box::choose_anchor_points() {
    QVector<AnchorPoint*> res;
    if (anch_type == BOX_GRID_3X3_SYMMETRIC) {
        QVector<int> pattern;
        int val0 = std::uniform_int_distribution<int>{0, 1}(rd);
        int val1 = std::uniform_int_distribution<int>{0, 1}(rd);
        int val2 = std::uniform_int_distribution<int>{0, 1}(rd);
        int val3 = std::uniform_int_distribution<int>{0, 1}(rd);
        int val4 = std::uniform_int_distribution<int>{0, 1}(rd);

        if(val0 == 1) {
            pattern.push_back(0);pattern.push_back(8);
        }
        if(val1 == 1) {
            pattern.push_back(1);pattern.push_back(7);
        }
        if(val2 == 1) {
            pattern.push_back(2);pattern.push_back(6);
        }
        if(val3 == 1) {
            pattern.push_back(3);pattern.push_back(5);
        }
        if(val4 == 1) {
            pattern.push_back(4);
        }

        for (int i = 0 ; i < anchor_points.size() ; ++i) {
            for (int j = 0 ; j < pattern.size() ; ++j) {
                res.push_back(&anchor_points[i][pattern[j]]);
            }
        }
    }
    else if (anch_type == BOX_GRID_4X4) {

    }
    else if (anch_type == BOX_GRID_3X3_RANDOM) {
        for (int i = 0 ; i < anchor_points.size() ; ++i) {
            if (anchor_points[i].size() == 0) continue;
            std::random_device rd;
            int ind_anchor = std::uniform_int_distribution<int>{0, anchor_points[i].size()-1}(rd);
            res.push_back(&anchor_points[i][ind_anchor]);
        }
    }
    else if (anch_type == BOX_ONE_FACE_ALIGNED) {
        for (int i = 0 ; i < anchor_points[0].size() ; ++i) {
            res.push_back(&anchor_points[0][i]);
        }
    }
    else {
        qDebug() << "ERROR BOX ANCH TYPE INVALID";
    }
    return res;
}

void Box::set_center() {
    if (anchor_point_prev_lvl == nullptr) {
        center = QVector3D(0,0,0);
    }
    else {
        QVector3D vec({anchor_point_prev_lvl->direction[0] * box_length/2,
                       anchor_point_prev_lvl->direction[1] * box_height/2,
                       anchor_point_prev_lvl->direction[2] * box_width/2});
        center = QVector3D(anchor_point_prev_lvl->coords + vec);
    }
}

void Box::set_rotation(QString box_part) {

}

void Box::generateRules(QString box_part) {
    set_rotation(box_part);
    if (box_part == "Simple3x3Rand" || box_part == "Simple3x3Sym" || box_part == "LongOneFace" || box_part == "SimpleEdge") {
        createLeafRulesSingle("cub", box_part, {box_length, box_height, box_width}, center, rotation);
    } else if(box_part == "SimpleAngles"){
        createLeafRulesSingle("cub", box_part, {box_length, box_height, box_width}, center, rotation);

        nut.set_main_cyl_radius(anchor_points[0][0].max_accepted_size);
        nut.set_main_cyl_length(anchor_points[0][0].max_accepted_size/3);
        nut.set_inter_cyl_radius(anchor_points[0][0].max_accepted_size/2);
        nut.createParams();

        QString rule = "";
        int nb_nut = anchor_points.size()*2;

        for(int j = 0; j < anchor_points.size(); j++){
            for (int i = 0 ; i < anchor_points[j].size() ; ++i) {
                nut.sentence = nut.base_sentence;
                nut.set_prev_anchor_point(&anchor_points[j][i]);
                nut.set_center();
                for (int k = 0 ; k < nut.primitives_str.size() ; ++k) {
                    nut.set_rotation(nut.primitives_str.at(k));
                    nut.generateRules(nut.primitives_str.at(k));
                }
                nut.set_anchor_points();
                AnchorPoint nutAnchorPoint = nut.anchor_points[0][0];

                nut.computeSentence();
                rule += nut.sentence;

                screw.set_body_width(nutAnchorPoint.max_accepted_size+0.03f);
                screw.set_prev_anchor_point(&nutAnchorPoint);
                screw.createParams();
                screw.set_center();
                for (int k = 0 ; k < screw.primitives_str.size() ; ++k) {
                    screw.set_rotation(screw.primitives_str.at(k));
                    screw.generateRules(screw.primitives_str.at(k));
                }

                rule += "+";
                screw.computeSentence();
                rule += screw.sentence;

                if (i != nb_nut-1) {
                    rule += "+";
                }
            }
            rules.insert(box_part, {rule});
        }
    }
    else if (box_part == "Relief3x3Rand" || box_part == "Relief3x3Sym" || box_part == "ReliefAngles" || box_part == "ReliefEdge") {
        QVector<QString> primitives({"cub", "cub", "cub", "cub", "cub", "cub", "cub"});
        QString op_bools ("------");
        QVector<float> params_main_cube({box_length + box_thickness*2, box_height + box_thickness*2, box_width + box_thickness*2});
        QVector<float> params_cube_x({   box_thickness*2,              box_height,                   box_width});
        QVector<float> params_cube_y({   box_length,                   box_thickness*2,              box_width});
        QVector<float> params_cube_z({   box_length,                   box_height,                   box_thickness*2});

        QVector3D center_cube_neg_x(center[0] - box_length/2 - box_thickness, center[1],                              center[2]                            );
        QVector3D center_cube_pos_x(center[0] + box_length /2+ box_thickness, center[1],                              center[2]                            );
        QVector3D center_cube_neg_y(center[0],                              center[1] - box_height/2 - box_thickness, center[2]                            );
        QVector3D center_cube_pos_y(center[0],                              center[1] + box_height/2 + box_thickness, center[2]                            );
        QVector3D center_cube_neg_z(center[0],                              center[1],                              center[2] - box_width/2 - box_thickness);
        QVector3D center_cube_pos_z(center[0],                              center[1],                              center[2] + box_width/2 + box_thickness);


        QVector<QVector<float>> params({params_main_cube, params_cube_x,     params_cube_x,     params_cube_y,     params_cube_y,     params_cube_z,     params_cube_z});
        QVector<QVector3D> centers(    {center,           center_cube_neg_x, center_cube_pos_x, center_cube_neg_y, center_cube_pos_y, center_cube_neg_z, center_cube_pos_z});
        QVector<QVector3D> rots({{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}});
        QString rule = createLeafRulesMultiple(primitives, op_bools, params, centers, rots);
        rules.insert(box_part, {rule});
    }
}

