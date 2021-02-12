#include "screwgenerator.h"

ScrewGenerator::ScrewGenerator()
{
    generator_name = "Screw";
    center = QVector3D(0,0,0);
}

void ScrewGenerator::generate(QString screw_part) {
    if (screw_part == "ScrewBodyCyl") {
        body_width = computeParameter(body_width, rd, 1.0f, 3.0f);
        body_precision = computeParameter(body_precision, rd, 10, 20);
        if (body_precision % 2 == 1) ++body_precision;
        body_height = computeParameter(body_height, rd, body_width*2,body_width*8);
        createLeafRulesSingle("cyl", screw_part, QVector3D(body_width, body_height, body_precision), QVector3D(center[0], center[1], center[2]), QVector3D(PI/2,PI/2,0));
    }
    else if (screw_part == "ScrewHeadCyl") {
        head_width = computeParameter(head_width, rd, body_width+1, body_width*2+1);
        int head_precision  = std::uniform_int_distribution<int>{7,12}(rd);
        if (head_precision % 2 == 1) ++head_precision;
        head_height = computeParameter(head_height, rd, 1.0f, head_width);
        createLeafRulesSingle("cyl", screw_part, QVector3D(head_width, head_height, head_precision), QVector3D(center[0], center[1] + body_height/2, center[2]), QVector3D(PI/2,PI/2,0));
    }
    else if (screw_part == "ScrewHeadCyl6") {
        head_width = computeParameter(head_width, rd, body_width+1, body_width*2+1);
        int head_precision  = 6;
        head_height = computeParameter(head_height, rd, 1.0f, head_width);
        createLeafRulesSingle("cyl", screw_part, QVector3D(head_width, head_height, head_precision), QVector3D(center[0], center[1] + body_height/2, center[2]), QVector3D(PI/2,PI/2,0));
    }
    else if (screw_part == "ScrewHeadCub") {
        head_width = computeParameter(head_width, rd, body_width*1.5f, body_width*2.5f);
        head_height = computeParameter(head_height, rd, 1.0f, head_width/2);
        createLeafRulesSingle("cub", screw_part, QVector3D(head_width, head_height, head_width), QVector3D(center[0], center[1] + body_height/2, center[2]), QVector3D(0,0,0));
    }
    else if (screw_part == "ScrewInterCyl6") {
        float inter_cyl_radius = (head_width + body_width) / 2;
        int inter_cyl_precision = body_precision;
        float inter_cyl_length = head_height;
        createLeafRulesSingle("cyl", screw_part, QVector3D(inter_cyl_radius, inter_cyl_length, inter_cyl_precision), QVector3D(center[0],center[1] + body_height/2 - head_height/2,center[2]), QVector3D(PI/2,PI/2,0));
    }
}


