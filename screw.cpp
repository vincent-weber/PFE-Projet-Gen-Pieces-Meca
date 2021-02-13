#include "screw.h"

Screw::Screw()
{
    generator_name = "Screw";
    center = QVector3D(0,0,0);
}

void Screw::generateParams(QString screw_part) {
    if (screw_part == "ScrewBodyCyl") {
        body_width = computeParameter(body_width, rd, 0.1f, 0.3f);
        body_precision = computeParameter(body_precision, rd, 10, 20);
        if (body_precision % 2 == 1) ++body_precision;
        body_height = computeParameter(body_height, rd, body_width*2,body_width*8);
    }
    else if (screw_part == "ScrewHeadCyl") {
        head_width = computeParameter(head_width, rd, body_width+0.1f, body_width*2+0.1f);
        head_precision = computeParameter(head_precision, rd, 7,12);
        if (head_precision % 2 == 1) ++head_precision;
        head_height = computeParameter(head_height, rd, 0.1f, head_width);
    }
    else if (screw_part == "ScrewHeadCyl6") {
        head_width = computeParameter(head_width, rd, body_width+0.1f, body_width*2+0.1f);
        head_height = computeParameter(head_height, rd, 0.1f, head_width);
    }
    else if (screw_part == "ScrewHeadCub") {
        head_width = computeParameter(head_width, rd, body_width*1.5f+0.1f, body_width*2.5f+0.1f);
        head_height = computeParameter(head_height, rd, 0.1f, head_width/2);
    }
    else if (screw_part == "ScrewInterCyl6") {

    }
}

void Screw::set_rotation(QVector3D direction, QString screw_part) {

    QVector3D vec_un(1,1,1);
    if (screw_part == "ScrewBodyCyl") {
        QVector3D vec_base(0,0,1);
        rotation = (vec_un - (vec_base + direction)) * PI/2;
    }
    else if (screw_part == "ScrewHeadCyl") {
        QVector3D vec_base(0,0,1);
        rotation = (vec_un - (vec_base + direction)) * PI/2;
    }
    else if (screw_part == "ScrewHeadCyl6") {
        QVector3D vec_base(0,0,1);
        rotation = (vec_un - (vec_base + direction)) * PI/2;
    }
    else if (screw_part == "ScrewHeadCub") {
        QVector3D vec_base(0,1,0);
        rotation = (vec_un - (vec_base + direction)) * PI/2;
    }
    else if (screw_part == "ScrewInterCyl6") {
        QVector3D vec_base(0,0,1);
        rotation = (vec_un - (vec_base + direction)) * PI/2;
    }
    qDebug() << "ROTATION DE" << rotation;
}

void Screw::generateRules(QString screw_part) {
    if (screw_part == "ScrewBodyCyl") {
        createLeafRulesSingle("cyl", screw_part, QVector<float>({body_width, body_height, (float)body_precision}), QVector3D(center[0], center[1], center[2]), rotation);
    }
    else if (screw_part == "ScrewHeadCyl") {
        createLeafRulesSingle("cyl", screw_part, QVector<float>({head_width, head_height, (float)head_precision}), QVector3D(center[0], center[1] + body_height/2, center[2]), rotation);
    }
    else if (screw_part == "ScrewHeadCyl6") {
        createLeafRulesSingle("cyl", screw_part, QVector<float>({head_width, head_height, 6}), QVector3D(center[0], center[1] + body_height/2, center[2]), rotation);
    }
    else if (screw_part == "ScrewHeadCub") {
        createLeafRulesSingle("cub", screw_part, QVector<float>({head_width, head_height, head_width}), QVector3D(center[0], center[1] + body_height/2, center[2]), rotation);
    }
    else if (screw_part == "ScrewInterCyl6") {
        float inter_cyl_radius = (head_width + body_width) / 2;
        int inter_cyl_precision = body_precision;
        float inter_cyl_length = head_height;
        createLeafRulesSingle("cyl", screw_part, QVector<float>({inter_cyl_radius, inter_cyl_length, (float)inter_cyl_precision}), QVector3D(center[0],center[1] + body_height/2 - head_height/2,center[2]), rotation);
    }
}



