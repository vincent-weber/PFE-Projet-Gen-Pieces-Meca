#include "butterflygenerator.h"

ButterflyGenerator::ButterflyGenerator()
{
    generator_name = "Butterfly";
}

void ButterflyGenerator::generate(QString part){
    if(part == "ButterflyBoby"){
        w = std::uniform_real_distribution<float>{5,8}(rd_gen);
        body_rad = std::uniform_real_distribution<float>{1,3}(rd_gen);
        body_len = std::uniform_real_distribution<float>{10, 20}(rd_gen);
        createLeafRulesSingle("cyl", part, QVector3D(body_rad, body_len, 20), QVector3D(0,0,0), QVector3D(PI/2,PI/2,0));
    } else if(part == "LeftWing"){
        createLeafRulesSingle("cub", part, QVector3D(body_rad,w,body_len/2), QVector3D(-(w+body_rad-0.1),0,0), QVector3D(PI/2,PI/2,0));
    } else if(part == "RightWing"){
        createLeafRulesSingle("cub", part, QVector3D(body_rad,w,body_len/2), QVector3D(w+body_rad-0.1,0,0), QVector3D(PI/2,PI/2,0));
    }
}
