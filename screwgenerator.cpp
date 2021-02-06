#include "screwgenerator.h"

ScrewGenerator::ScrewGenerator()
{
    generator_name = "Screw";
}

void ScrewGenerator::generate(QString screw_part) {
    if (screw_part == "ScrewBodyCyl") {
        float body_radius = std::uniform_real_distribution<float>{1,3}(rd);
        body_width = body_radius;
        body_precision  = std::uniform_int_distribution<int>{10,20}(rd);
        if (body_precision % 2 == 1) ++body_precision;
        float body_length = std::uniform_real_distribution<float>{body_radius*2,body_radius*8}(rd);
        body_height = body_length;
        createLeafRules("cyl", screw_part, QVector3D(body_radius, body_length, body_precision), QVector3D(0,0,0), QVector3D(PI/2,PI/2,0));
    }
    else if (screw_part == "ScrewHeadCyl") {
        float head_radius = std::uniform_real_distribution<float>{body_width+1, body_width*2+1}(rd);
        head_width = head_radius;
        int head_precision  = std::uniform_int_distribution<int>{7,12}(rd);
        if (head_precision % 2 == 1) ++head_precision;
        float head_length = std::uniform_real_distribution<float>{1,head_radius}(rd);
        head_height = head_length;
        createLeafRules("cyl", screw_part, QVector3D(head_radius, head_length, head_precision), QVector3D(0,body_height/2,0), QVector3D(PI/2,PI/2,0));
    }
    else if (screw_part == "ScrewHeadCyl6") {
        float head_radius = std::uniform_real_distribution<float>{body_width+1, body_width*2+1}(rd);
        head_width = head_radius;
        int head_precision  = 6;
        float head_length = std::uniform_real_distribution<float>{1,head_radius}(rd);
        head_height = head_length;
        createLeafRules("cyl", screw_part, QVector3D(head_radius, head_length, head_precision), QVector3D(0,body_height/2,0), QVector3D(PI/2,PI/2,0));
    }
    else if (screw_part == "ScrewHeadCub") {
        float head_side_length = std::uniform_real_distribution<float>{body_width*1.5f, body_width*2.5f}(rd);
        head_width = head_side_length;
        float head_height = std::uniform_real_distribution<float>{1,head_side_length/2}(rd);
        this->head_height = head_height;
        createLeafRules("cub", screw_part, QVector3D(head_side_length, head_height, head_side_length), QVector3D(0,body_height/2,0), QVector3D(0,0,0));
    }
    else if (screw_part == "ScrewInterCyl6") {
        float inter_cyl_radius = (head_width + body_width) / 2;
        int inter_cyl_precision = body_precision;
        float inter_cyl_length = head_height;
        createLeafRules("cyl", screw_part, QVector3D(inter_cyl_radius, inter_cyl_length, inter_cyl_precision), QVector3D(0,body_height/2 - head_height/2,0), QVector3D(PI/2,PI/2,0));
    }
}


