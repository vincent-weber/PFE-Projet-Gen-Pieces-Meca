#include "piston.h"

Piston::Piston()
{
    generator_name = "Piston";
    center = QVector3D(0,0,0);
    rotation = QVector3D(0,0,0);
}

//x : legth, y = height, z = width;
void Piston::generateParams(QString part){
    float max_value = get_max_possible_size();
    if(part == "HeadCyl"){
        head_width = computeParameter(head_width, rd, 0.1f, max_value);
        head_precision = computeParameter(head_precision, rd, 10, 20);
        if (head_precision % 2 == 1) ++head_precision;
        head_height = computeParameter(head_height, rd, 0.1f, head_width);
    }
    else if(part == "HeadIntersect"){
        head_inter_width = computeParameter(head_inter_width, rd, 0.1, head_width-1);
    }
    else if(part == "BodyCuboid"){
        body_height = computeParameter(body_height, rd, 5.0f, max_value);
        body_width = computeParameter(body_width, rd, 5.0f, max_value);
        body_length = computeParameter(body_length, rd, 5.0f, max_value);
    }
    else if(part == "EndCyl"){
        endCyl_width = computeParameter(endCyl_width, rd, 0.1f, max_value);
        endCyl_precision = computeParameter(endCyl_precision, rd, 10, 20);
        if (endCyl_precision % 2 == 1) ++endCyl_precision;
        endCyl_height = computeParameter(endCyl_height, rd, 0.1f,endCyl_width);
    }
    else if(part == "EndIntersect"){
        endCyl_inter_width = computeParameter(endCyl_inter_width, rd, 0.1, endCyl_width);
    }
}

void Piston::set_rotation(QString part){
    QVector3D vec_un(1,1,1);
    QVector3D vec_base;

    if(part == "HeadCyl"){
        vec_base= QVector3D(0,0,1);
    }
    else if(part == "HeadIntersect"){
        vec_base= QVector3D(0,0,1);
    }
    else if(part == "BodyCuboid"){
        vec_base= QVector3D(0,1,0);
    }
    else if(part == "EndCyl"){
        vec_base= QVector3D(0,0,1);
    }
    else if(part == "EndIntersect"){
        vec_base= QVector3D(0,0,1);
    }

    if(vec_base == direction || vec_base == -direction) {
        rotation = QVector3D(0,0,0);
    }
    else rotation = (vec_un - (vec_base + direction)) * PI/2;
}

void Piston::set_center(){
    QVector3D vecteurBody(body_length + head_height, body_height + head_height, body_width + head_height);
    QVector3D offset = - anchor_point_prev_lvl->direction*0.001;
    center = QVector3D(anchor_point_prev_lvl->coords + anchor_point_prev_lvl->direction*vecteurBody + offset);
}

void Piston::set_anchor_points(){

}

//x : legth, y = height, z = width;
void Piston::generateRules(QString part){
    set_rotation(part);

    QVector3D centerBody = center;
    QVector3D centerHead(center[0] + body_length/2 + head_height/2 * direction[0], center[1] + body_height/2 + head_height/2 * direction[1], center[2] + body_width/2 + head_height/2 *direction[2]);
    QVector3D centerEnd(center[0] + body_length/2 + endCyl_width/2 * direction[0], center[1] + body_height/2 + endCyl_width/2 * direction[1], center[2] + body_width/2 + endCyl_width/2 *direction[2]);

    if(part == "HeadCyl"){
        createLeafRulesSingle("cyl", part, QVector<float>({head_width, body_height, (float)head_precision}), centerHead, rotation);
    }
    else if(part == "HeadIntersect"){
        createLeafRulesSingle("cyl", part, QVector<float>({head_inter_width, head_height, (float)head_precision}), centerHead, rotation);
    }
    else if(part == "BodyCuboid"){
        createLeafRulesSingle("cub", part, QVector<float>({body_width, body_height, body_length}), centerBody, rotation);
    }
    else if(part == "EndCyl"){
        createLeafRulesSingle("cyl", part, QVector<float>({endCyl_width, endCyl_height, (float)endCyl_precision}), centerEnd, rotation);
    }
    else if(part == "EndIntersect"){
        createLeafRulesSingle("cyl", part, QVector<float>({endCyl_inter_width, endCyl_height, (float)endCyl_precision}), centerEnd, rotation);
    }
}
