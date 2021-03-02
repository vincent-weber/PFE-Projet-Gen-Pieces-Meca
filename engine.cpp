#include "engine.h"

Engine::Engine()
{
    generator_name = "Engine";
    max_size = 0.6f;
}

void Engine::generateParams(QString engine_part) {
    float max_value = get_max_possible_size();
    if (engine_part == "CubHeadEngine" || engine_part == "CylHeadEngine") {
        head_width = computeParameter(head_width, rd, 0.1f, max_value);
        head_length = computeParameter(head_length, rd, head_width / 2, head_width);
    }
    else if (engine_part == "CylMainAxe") {
        pipe_width = computeParameter(pipe_width, rd, head_width / 4, head_width * 0.75f);
        pipe_length = computeParameter(pipe_length, rd, 3.0f, 6.0f);
    }
    else if (engine_part == "CubExtEngine" || engine_part == "CylExtEngine") {
        end_width = computeParameter(end_width, rd, pipe_width / 2, pipe_width * 0.75f);
        end_length = computeParameter(end_length, rd, pipe_length / 10, pipe_length / 5);
    }

    else if (engine_part == "AlignedPistons4" || engine_part == "AlternatedPistons4") {
        nb_pistons = 4;
        pistons_gap = pipe_length / (nb_pistons * 3);

    }

    else if (engine_part == "CylSeparators" || engine_part == "CubSeparators") {
        sep_width = computeParameter(end_width, rd, (pipe_width + head_width) / 2, head_width);
        sep_length = (pipe_length - (nb_pistons+1) * pistons_gap) / nb_pistons * 2;
    }

}

void Engine::set_rotation(QString engine_part) {
    QVector3D vec_un(1,1,1);
    QVector3D vec_base;

    if (engine_part == "CubHeadEngine") {
        vec_base= QVector3D(0,1,0);
    }
    else if (engine_part == "CylHeadEngine") {
        vec_base= QVector3D(0,0,1);
    }
    else if (engine_part == "CylMainAxe") {
        vec_base = QVector3D(0,0,1);
    }
    else if (engine_part == "CubExtEngine") {
        vec_base = QVector3D(0,1,0);
    }
    else if (engine_part == "CylExtEngine") {
        vec_base = QVector3D(0,0,1);
    }

    if(vec_base == direction || vec_base == -direction) {
        rotation = QVector3D(0,0,0);
    }
    else rotation = (vec_un - (vec_base + direction)) * PI/2;
}

void Engine::set_center() {
    QVector3D offset = - anchor_point_prev_lvl->direction*0.001;
    center = QVector3D(anchor_point_prev_lvl->coords + anchor_point_prev_lvl->direction*((head_length) +pipe_length/2) + offset);
}

void Engine::generateRules(QString engine_part) {
    set_rotation(engine_part);
    if (engine_part == "CubHeadEngine") {
        QVector3D center_cyl_head = center - direction * (pipe_length/2 + head_length/2);
        createLeafRulesSingle("cub", engine_part, QVector<float>({head_width, head_length, head_width}), center_cyl_head, rotation);
    }
    else if (engine_part == "CylHeadEngine") {
        QVector3D center_cyl_head = center - direction * (pipe_length/2 + head_length/2);
        createLeafRulesSingle("cyl", engine_part, QVector<float>({head_width, head_length, precision}), center_cyl_head, rotation);
    }
    else if (engine_part == "CylMainAxe") {
        createLeafRulesSingle("cyl", engine_part, QVector<float>({pipe_width, pipe_length, precision}), center, rotation);
    }
    else if (engine_part == "CubExtEngine") {
        QVector3D center_cyl_ext = center + direction * (pipe_length/2 + end_length/2);
        createLeafRulesSingle("cub", engine_part, QVector<float>({end_width, end_length, end_width}), center_cyl_ext, rotation);
    }
    else if (engine_part == "CylExtEngine") {
        QVector3D center_cyl_ext = center + direction * (pipe_length/2 + end_length/2);
        createLeafRulesSingle("cyl", engine_part, QVector<float>({end_width, end_length, precision}), center_cyl_ext, rotation);
    }

    else if (engine_part == "AlignedPistons4" || engine_part == "AlternatedPistons4") {

    }

    else if (engine_part == "CylSeparators" || engine_part == "CubSeparators") {

    }

}

void Engine::set_anchor_points() {

}

QVector<AnchorPoint> Engine::choose_anchor_points() {
    return {};
}
