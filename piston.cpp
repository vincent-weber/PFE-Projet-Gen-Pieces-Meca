#include "piston.h"

Piston::Piston()
{
    generator_name = "Piston";
    center = QVector3D(0,0,0);
    rotation = QVector3D(0,0,0);
}

//x : length, y = height, z = width;
void Piston::generateParams(QString part){
    if(part == "HeadCyl"){
        head_width = computeParameter(head_width, rd, 0.3f, 0.6f);
        head_precision = computeParameter(head_precision, rd, 10,  20);
        if (head_precision % 2 == 1) ++head_precision;
        head_height = computeParameter(head_height, rd, 0.3f, head_width);
    }
    else if(part == "HeadIntersect"){
        head_inter_width = computeParameter(head_inter_width, rd, head_height/2 * 0.33f, head_height/2 * 0.75f);
//        qDebug() << "TESTS" << head_inter_width << head_height;
    }
    else if(part == "BodyCuboid"){
        body_height = computeParameter(body_height, rd, head_height, head_height*2);
        body_width = computeParameter(body_width, rd, head_width/4, head_width/2);
        body_length = computeParameter(body_length, rd, head_width/4, head_width/2);
    }
    else if(part == "EndCyl"){
        float min_val = min(body_length, body_width);
        endCyl_width = computeParameter(endCyl_width, rd, min_val/2, min_val);
        endCyl_precision = computeParameter(endCyl_precision, rd, 10, 20);
        if (endCyl_precision % 2 == 1) ++endCyl_precision;
        endCyl_height = computeParameter(endCyl_height, rd, min_val/2, min_val);
    }
    else if(part == "EndIntersect"){
        endCyl_inter_width = computeParameter(endCyl_inter_width, rd, endCyl_width/4, endCyl_width/2);
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
    else if(part == "EndCyl" || part == "EndIntersect"){
        rotation = head_intersect_rot;
        return;
    }

    if(vec_base == direction || vec_base == -direction) {
        rotation = QVector3D(0,0,0);
    }
    else rotation = (vec_un - (vec_base + direction)) * PI/2;

    if (part == "HeadIntersect") {
        rotation = rotation + QVector3D(PI/2,PI/2,0);
        head_intersect_rot = rotation;
    }
}

void Piston::set_center(){
    QVector3D vector(endCyl_width, endCyl_width, endCyl_width);
    QVector3D offset = -anchor_point_prev_lvl->direction*0.001;
    center = QVector3D(anchor_point_prev_lvl->coords + offset);
}

void Piston::set_anchor_points(){

}

QVector<AnchorPoint> Piston::choose_anchor_points() {
    return {};
}

//x : legth, y = height, z = width;
void Piston::generateRules(QString part){
    set_rotation(part);
    float offset = endCyl_width / 4;
    QVector3D centerEnd(center[0], center[1], center[2]);
    QVector3D centerBody(centerEnd[0] + (endCyl_width + body_height/2 - offset) * direction[0], centerEnd[1] + (endCyl_width + body_height/2 - offset) * direction[1], centerEnd[2] + (endCyl_width + body_height/2 - offset) * direction[2]);
    QVector3D centerHead(centerBody[0] + (head_height/2 + body_length/2) * direction[0], centerBody[1] + (head_height/2 + body_height/2) * direction[1], centerBody[2] + (head_height/2 + body_width/2) * direction[2]);

    if(part == "HeadCyl"){
        createLeafRulesSingle("cyl", part, QVector<float>({head_width, head_height, (float)head_precision}), centerHead, rotation);
    }
    else if(part == "HeadIntersect"){
        createLeafRulesSingle("cyl", part, QVector<float>({head_inter_width, head_width*2, (float)head_precision}), centerHead, rotation);
    }
    else if(part == "BodyCuboid"){
        createLeafRulesSingle("cub", part, QVector<float>({body_length, body_height, body_width}), centerBody, rotation);
    }
    else if(part == "EndCyl"){
        createLeafRulesSingle("cyl", part, QVector<float>({endCyl_width, endCyl_height, (float)endCyl_precision}), centerEnd, rotation);
    }
    else if(part == "EndIntersect"){
        createLeafRulesSingle("cyl", part, QVector<float>({endCyl_inter_width, endCyl_height, (float)endCyl_precision}), centerEnd, rotation);
    }
}
