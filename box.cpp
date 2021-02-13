#include "box.h"

Box::Box()
{
    generator_name = "Box";
}

//TODO : stocker les 4 centres des 4 cylindres pour les vis
void Box::generateParams(QString box_part) {
    if (box_part == "BoiteCube") {
        box_height = computeParameter(box_height, rd, 5.0f, 10.0f);
        box_width = computeParameter(box_width, rd, 5.0f, 10.0f);
        box_length = computeParameter(box_length, rd, 5.0f, 10.0f);

        box_thickness = computeParameter(box_thickness, rd, 0.5f, 1.5f);

        QVector<QString> primitives({"cub", "cub"});
        QString op_bools ("-");
        QVector<QVector<float>> params({{box_length + box_thickness*2, box_height + box_thickness*2, box_width + box_thickness*2}, {box_length, box_height + box_thickness*2, box_width}});
        QVector<QVector3D> centers({{0,0,0}, {0,box_thickness,0}});
        QVector<QVector3D> rots({{0,0,0},{0,0,0}});
        QString rule = createLeafRulesMultiple(primitives, op_bools, params, centers, rots);
        rules.insert(box_part, {rule});
    }
    else if (box_part == "BoiteRelief") {
        box_height = computeParameter(box_height, rd, 5.0f, 10.0f);
        box_width = computeParameter(box_width, rd, 5.0f, 10.0f);
        box_length = computeParameter(box_length, rd, 5.0f, 10.0f);

        box_thickness = computeParameter(box_thickness, rd, 0.5f, 1.5f);
        QVector<float> params({box_length, box_height, box_width});
        QVector3D center({0,0,0});
        QVector3D rot({0,0,0});
        createLeafRulesSingle("cub", box_part, params, center, rot);
    }
    else if (box_part == "AncrageGrille3x3") {
        //haut et bas de la boite
        float offset_x = box_length/4;
        float offset_z = box_width/4;
        float y = center.y() + box_height/2;
        float x = center.x() + offset_x;
        float z = center.z() + offset_z;

        QVector3D bounding_box(box_length/4,0,box_width/4);
        for (int i = 0 ; i < 3 ; ++i) {
            QVector<AnchorPoint> anchor_ps;
            for (int j = 0 ; j < 3 ; ++j) {
                QVector3D coords(x,y,z);
                QVector3D coords2(x,y-box_height,z);
                QVector3D direction(0,0,1);
                QVector3D rotation(0,0,0);
                AnchorPoint anch(coords, direction, rotation, bounding_box);
                AnchorPoint anch2(coords2, -direction, rotation, bounding_box);
                anchor_ps.push_back(anch);
                anchor_ps.push_back(anch2);
                x -= offset_x;
            }
            x = center.x() + offset_x;
            z -= offset_z;
            anchor_points.push_back(anchor_ps);
        }

        //fond et devant de la boite
        offset_x = box_length/4;
        float offset_y = box_height/4;
        z = center.z() + box_width/2;
        x = center.x() + offset_x;
        y = center.y() + offset_y;

        bounding_box = QVector3D(box_length/4,box_height/4,0);
        for (int i = 0 ; i < 3 ; ++i) {
            QVector<AnchorPoint> anchor_ps;
            for (int j = 0 ; j < 3 ; ++j) {
                QVector3D coords(x,y,z);
                QVector3D coords2(x,y,z-box_width);
                QVector3D direction(0,1,0);
                QVector3D rotation(0,0,0);
                AnchorPoint anch(coords, direction, rotation, bounding_box);
                AnchorPoint anch2(coords2, -direction, rotation, bounding_box);
                anchor_ps.push_back(anch);
                anchor_ps.push_back(anch2);
                x -= offset_x;
            }
            x = center.x() + offset_x;
            y -= offset_y;
            anchor_points.push_back(anchor_ps);
        }

        //gauche et droite de la boite
        offset_y = box_height/4;
        offset_z = box_width/4;
        x = center.x() + box_length/2;
        y = center.y() + offset_y;
        z = center.z() + offset_z;

        bounding_box = QVector3D(0,box_height/4,box_width/4);
        for (int i = 0 ; i < 3 ; ++i) {
            QVector<AnchorPoint> anchor_ps;
            for (int j = 0 ; j < 3 ; ++j) {
                QVector3D coords(x,y,z);
                QVector3D coords2(x-box_length,y,z);
                QVector3D direction(1,0,0);
                QVector3D rotation(0,0,0);
                AnchorPoint anch(coords, direction, rotation, bounding_box);
                AnchorPoint anch2(coords2, -direction, rotation, bounding_box);
                anchor_ps.push_back(anch);
                anchor_ps.push_back(anch2);
                z -= offset_z;
            }
            z = center.z() + offset_z;
            y -= offset_y;
            anchor_points.push_back(anchor_ps);
        }

        /*qDebug() << "VERIF POINTS ANCRAGE : ";
        for (int i = 0 ; i < anchor_points.size() ; ++i) {
            for (int j = 0 ; j < anchor_points[0].size() ; ++j) {
                qDebug() << anchor_points[i][j].coords;
            }
        }*/
        rules.insert("AncrageGrille3x3", {""});
    }

    else if (box_part == "VisAnglesBoiteCub") {
        screw_spot_thickness = computeParameter(screw_spot_thickness, rd, 0.3f, 1.0f);
        screws_width = computeParameter(screws_width, rd, box_length/16, box_length/8);
        screws_precision = computeParameter(screws_precision, rd, 10, 20);

        QVector<QVector3D> centers({{box_length - screw_spot_thickness - screws_width + box_thickness/2, box_thickness/2 - 0.01f, box_width - screw_spot_thickness - screws_width + box_thickness/2},
                                    {box_length - screw_spot_thickness - screws_width + box_thickness/2, box_thickness/2  - 0.01f, -(box_width - screw_spot_thickness - screws_width) - box_thickness/2},
                                    {-(box_length - screw_spot_thickness - screws_width) - box_thickness/2, box_thickness/2  - 0.01f, -(box_width - screw_spot_thickness - screws_width) - box_thickness/2},
                                    {-(box_length - screw_spot_thickness - screws_width) - box_thickness/2, box_thickness/2  - 0.01f, box_width - screw_spot_thickness - screws_width + box_thickness/2}});

        QString rule = "";
        for (int i = 0 ; i < 4 ; ++i) {
            QVector<QString> primitives({"cyl", "cyl"});
            QString op_bools ("-");
            QVector<QVector<float>> params({{screws_width + screw_spot_thickness, (box_height + box_thickness*1.5f)*2, (float)screws_precision}, {screws_width, (box_height + box_thickness*1.5f)*2, (float)screws_precision}});
            QVector<QVector3D> c({centers[i], centers[i]});

            QVector<QVector3D> rots({{PI/2,PI/2,0},{PI/2,PI/2,0}});
            rule += createLeafRulesMultiple(primitives, op_bools, params, c, rots);
            if (i != 3) {
                rule += "+";
            }
        }
        rules.insert(box_part, {rule});
    }
}

void Box::set_rotation(QVector3D direction, QString screw_part) {

}

void Box::generateRules(QString screw_part) {

}
