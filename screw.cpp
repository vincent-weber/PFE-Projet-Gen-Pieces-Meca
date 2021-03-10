#include "screw.h"

Screw::Screw()
{
    generator_name = "Screw";
    center = QVector3D(0,0,0);
    direction = QVector3D(0,0,1);
    max_size = 0.5f;
}

void Screw::generateParams(QString screw_part) {

    float max_value = get_max_possible_size();

    if (screw_part == "ScrewBodyCyl") {
        body_width = computeParameter(body_width, rd, 0.1f, max_value);
        body_precision = computeParameter(body_precision, rd, 10, 20);
        if (body_precision % 2 == 1) ++body_precision;
        body_height = computeParameter(body_height, rd, body_width*1.5,body_width*2.5);
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
        head_width = computeParameter(head_width, rd, body_width*2.5f+0.1f, body_width*3.5f+0.1f);
        head_height = computeParameter(head_height, rd, 0.1f, head_width/2);
    }
    else if (screw_part == "ScrewInterCyl6") {

    }
}

void Screw::set_center() {
    QVector3D offset = - anchor_point_prev_lvl->direction*0.001;
    center = QVector3D(anchor_point_prev_lvl->coords - anchor_point_prev_lvl->direction*((body_height/2) - head_height/2) + offset);
}

void Screw::set_rotation(QString screw_part) {
    QVector3D vec_un(1,1,1);
    QVector3D vec_base;

    if (screw_part == "ScrewBodyCyl") {
        vec_base= QVector3D(0,0,1);
    }
    else if (screw_part == "ScrewHeadCyl") {
        vec_base= QVector3D(0,0,1);
    }
    else if (screw_part == "ScrewHeadCyl6") {
        vec_base = QVector3D(0,0,1);
    }
    else if (screw_part == "ScrewHeadCub") {
        vec_base = QVector3D(0,1,0);
    }
    else if (screw_part == "ScrewInterCyl6") {
        vec_base = QVector3D(0,0,1);
    }

    if(vec_base == direction || vec_base == -direction) {
        rotation = QVector3D(0,0,0);
    }
    else rotation = (vec_un - (vec_base + direction)) * PI/2;
}

void Screw::set_anchor_points() {

}

QVector<AnchorPoint*> Screw::choose_anchor_points() {
    return {};
}

void Screw::generateRules(QString screw_part) {

    QVector3D centerBody(center[0], center[1], center[2]);
    QVector3D centerHead(center[0] + body_height/2 * direction[0], center[1] + body_height/2 * direction[1], center[2] + body_height/2 *direction[2]);
    QVector3D centerInterCyl(center[0] + (body_height/2 - head_height/2) * direction[0], center[1] + (body_height/2 - head_height/2) * direction[1], center[2] + (body_height/2 - head_height/2) *direction[2]);

    if (screw_part == "ScrewBodyCyl") {
        createLeafRulesSingle("cyl", screw_part, QVector<float>({body_width, body_height, (float)body_precision}), centerBody, rotation);
    }
    else if (screw_part == "ScrewHeadCyl") {
        createLeafRulesSingle("cyl", screw_part, QVector<float>({head_width, head_height, (float)head_precision}), centerHead, rotation);
    }
    else if (screw_part == "ScrewHeadCyl6") {
        createLeafRulesSingle("cyl", screw_part, QVector<float>({head_width, head_height, 6}), centerHead, rotation);
    }
    else if (screw_part == "ScrewHeadCub") {
        createLeafRulesSingle("cub", screw_part, QVector<float>({head_width, head_height, head_width}), centerHead, rotation);
    }
    else if (screw_part == "ScrewInterCyl6") {
        float inter_cyl_radius = (head_width + body_width) / 2;
        int inter_cyl_precision = body_precision;
        float inter_cyl_length = head_height;
        createLeafRulesSingle("cyl", screw_part, QVector<float>({inter_cyl_radius, inter_cyl_length, (float)inter_cyl_precision}), centerInterCyl, rotation);
    }
}
