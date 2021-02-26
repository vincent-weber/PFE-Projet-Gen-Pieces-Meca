#include "pipe.h"

Pipe::Pipe()
{
    generator_name = "Pipe";
    max_size = 0.75f;
}

void Pipe::generateParams(QString pipe_part) {
    if (pipe_part == "ClassicCyl") {

        float max_value = get_max_possible_size();
        radius = computeParameter(radius, rd, 0.15f, max_value);
        precision = computeParameter(precision, rd, 10, 20);
        if (precision % 2 == 1) ++precision;
        length = computeParameter(length, rd, radius*2,radius*5);
    }
}

void Pipe::set_center() {
    QVector3D offset = - anchor_point_prev_lvl->direction*0.001;
    center = QVector3D(anchor_point_prev_lvl->coords + anchor_point_prev_lvl->direction*(length/2)) + offset;
}

void Pipe::set_rotation(QString pipe_part) {
    QVector3D vec_un(1,1,1);
    //ici vec_base a 1 car les pipes sont tjrs des cylindres pour le moment mais changer et faire des if (pipe_part == ...)
    //si on veut rajouter un tuyau en forme de cuboide par ex.
    QVector3D vec_base(0,0,1);

    if(vec_base == direction || vec_base == -direction) {
        rotation = QVector3D(0,0,0);
    }
    else rotation = (vec_un - (vec_base + direction)) * PI/2;
}

void Pipe::set_anchor_points() {
    float x = center[0] + direction[0] * (length/2);
    float y = center[1] + direction[1] * (length/2);
    float z = center[2] + direction[2] * (length/2);

    QVector<AnchorPoint> anchor_point1;
    float max_accepted_size = radius;
    QVector3D coords(x,y,z);
    AnchorPoint anch_point(coords, direction, max_accepted_size);
    QVector3D coords_used_anchor_point = anchor_point_prev_lvl->coords;
    float dist = coords_used_anchor_point.distanceToPoint(coords);
    if (dist > min_distance_between_anchor_points) {
        anchor_point1.push_back(anch_point);
    }

    float x2 = center[0] + direction[0] * (-length/2);
    float y2 = center[1] + direction[1] * (-length/2);
    float z2 = center[2] + direction[2] * (-length/2);

    QVector<AnchorPoint> anchor_point2;
    max_accepted_size = radius;
    coords = QVector3D(x2,y2,z2);
    AnchorPoint anch_point2(coords, direction, max_accepted_size);
    coords_used_anchor_point = anchor_point_prev_lvl->coords;
    dist = coords_used_anchor_point.distanceToPoint(coords);
    if (dist > min_distance_between_anchor_points) {
        anchor_point2.push_back(anch_point2);
    }
    anchor_points.push_back(anchor_point1);
    anchor_points.push_back(anchor_point2);
}

void Pipe::generateRules(QString pipe_part) {
    createLeafRulesSingle("cyl", pipe_part, QVector<float>({radius, length, (float)precision}), center, rotation);
}

