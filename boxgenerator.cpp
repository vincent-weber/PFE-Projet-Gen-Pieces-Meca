#include "boxgenerator.h"

BoxGenerator::BoxGenerator()
{
    generator_name = "Box";
}

void BoxGenerator::generate(QString box_part) {
    if (box_part == "BoiteCube") {
        box_height = computeParameter(box_height, rd, 5.0f, 10.0f);
        box_width = computeParameter(box_width, rd, 5.0f, 10.0f);
        box_length = computeParameter(box_length, rd, 5.0f, 10.0f);

        box_thickness = computeParameter(box_thickness, rd, 0.5f, 1.5f);

        QVector<QString> primitives({"cub", "cub"});
        QString op_bools ("-");
        QVector<QVector3D> params({{box_length + box_thickness*2, box_height + box_thickness*2, box_width + box_thickness*2}, {box_length, box_height + box_thickness*2, box_width}});
        QVector<QVector3D> centers({{0,0,0}, {0,box_thickness,0}});
        QVector<QVector3D> rots({{0,0,0},{0,0,0}});
        QString rule = createLeafRulesMultiple(primitives, op_bools, params, centers, rots);
        rules.insert(box_part, {rule});
    }
    else if (box_part == "VisAnglesBoiteCub") {
        screw_spot_thickness = computeParameter(screw_spot_thickness, rd, 0.3f, 1.0f);
        screws_width = computeParameter(screws_width, rd, box_length/16, box_length/8);
        screws_precision = computeParameter(screws_precision, rd, 10, 20);

        QVector<QVector3D> centers({{box_length - screw_spot_thickness - screws_width + box_thickness/2, box_thickness/2, box_width - screw_spot_thickness - screws_width + box_thickness/2},
                                    {box_length - screw_spot_thickness - screws_width + box_thickness/2, box_thickness/2, -(box_width - screw_spot_thickness - screws_width) - box_thickness/2},
                                    {-(box_length - screw_spot_thickness - screws_width) - box_thickness/2, box_thickness/2, -(box_width - screw_spot_thickness - screws_width) - box_thickness/2},
                                    {-(box_length - screw_spot_thickness - screws_width) - box_thickness/2, box_thickness/2, box_width - screw_spot_thickness - screws_width + box_thickness/2}});

        QString rule = "";
        for (int i = 0 ; i < 4 ; ++i) {
            QVector<QString> primitives({"cyl", "cyl"});
            QString op_bools ("-");
            QVector<QVector3D> params({{screws_width + screw_spot_thickness, (box_height + box_thickness*1.5f)*2, (float)screws_precision}, {screws_width, (box_height + box_thickness*1.5f)*2, (float)screws_precision}});
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
