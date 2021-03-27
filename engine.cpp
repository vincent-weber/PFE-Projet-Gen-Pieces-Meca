#include "engine.h"

Engine::Engine()
{
    generator_name = "Engine";
    max_size = 0.6f;
    min_size = 0.1f;
}

void Engine::generateParams(QString engine_part) {
    float max_value = get_max_possible_size();
    float min_value = min_size;
    if (max_value < min_value) {
        max_value = min_value;
    }
    if (engine_part == "CubHeadEngine" || engine_part == "CylHeadEngine") {
        head_width = computeParameter(head_width, rd, min_value, max_value);
        head_length = computeParameter(head_length, rd, head_width / 2, head_width);
    }
    else if (engine_part == "CylMainAxe") {
        pipe_width = computeParameter(pipe_width, rd, head_width * 0.25f, head_width * 0.75f);
        pipe_length = computeParameter(pipe_length, rd, pipe_length_min, pipe_length_max);
    }
    else if (engine_part == "CubExtEngine" || engine_part == "CylExtEngine") {
        end_width = computeParameter(end_width, rd, pipe_width * 0.5f, pipe_width * 0.75f);
        end_length = computeParameter(end_length, rd, pipe_length / 10, pipe_length / 5);
    }

    else if (engine_part == "Aligned4All" || engine_part == "Aligned4Rand" || engine_part == "Alternated4All" || engine_part == "Alternated4Rand") {
        nb_pistons = 4;
        pistons_gap = pipe_length * (1.0f/((nb_pistons+1)+nb_pistons*2));
        if (engine_part == "Aligned4All") {
            anch_type = ENGINE_ALIGNED_ALL;
        }
        else if (engine_part == "Aligned4Rand") {
            anch_type = ENGINE_ALIGNED_RANDOM;
        }
        else if (engine_part == "Alternated4All") {
            anch_type = ENGINE_ALTERNATED_ALL;
        }
        else if (engine_part == "Alternated4Rand") {
            anch_type = ENGINE_ALTERNATED_RANDOM;
        }
        piston.set_end_cyl_intersect_width(pipe_width * 0.998f);
        piston.set_end_cyl_width((pipe_width*1.5f));
        piston.createParams();
    }
    else if (engine_part == "AlignedNRand" || engine_part == "AlternatedNRand" || engine_part == "AlignedNAll" || engine_part == "AlternatedNAll") {
        //* 4 = 16 pistons max, *2 = 8 pistons max
        nb_pistons = (pipe_length / pipe_length_min) * 2;
        pistons_gap = pipe_length * (1.0f/((nb_pistons+1)+nb_pistons*2));
        if (engine_part == "AlignedNRand") {
            anch_type = ENGINE_ALIGNED_RANDOM;
        }
        else if (engine_part == "AlternatedNRand") {
            anch_type = ENGINE_ALTERNATED_RANDOM;
        }
        else if (engine_part == "AlignedNAll") {
            anch_type = ENGINE_ALIGNED_ALL;
        }
        else if (engine_part == "AlternatedNAll") {
            anch_type = ENGINE_ALTERNATED_ALL;
        }

        piston.set_end_cyl_intersect_width(pipe_width * 0.998f);
        piston.set_end_cyl_width((pipe_width*1.5f));
        piston.createParams();
    }

    else if (engine_part == "CylSeparators" || engine_part == "CubSeparators") {
        //sep_width = computeParameter(sep_width, rd, (pipe_width + head_width) / 2, head_width);
        sep_width = head_width;
        sep_length = pistons_gap / 2;
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
    else if (engine_part == "CylSeparators") {
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

void Engine::set_anchor_points() {

    QVector3D center_cyl_head = center - direction * (pipe_length/2 + head_length/2);
    QVector<AnchorPoint> anch_points;
    QVector3D dir_anch_p;
    if (direction[0] == 1) {
        dir_anch_p = QVector3D(0,1,0);
    }
    else if (direction[0] == -1) {
        dir_anch_p = QVector3D(0,-1,0);
    }
    else if (direction[1] == 1) {
        dir_anch_p = QVector3D(0,0,1);
    }
    else if (direction[1] == -1) {
        dir_anch_p = QVector3D(0,0,-1);
    }
    else if (direction[2] == 1) {
        dir_anch_p = QVector3D(1,0,0);
    }
    else if (direction[2] == -1) {
        dir_anch_p = QVector3D(-1,0,0);
    }

    QVector3D coords(center_cyl_head + direction * (head_length/2 + pistons_gap * 1.5f + sep_length));

    float offset_other_direction = sep_width - pipe_width;
    float offset_piston = pistons_gap * 2 + sep_length * 2;
    for (int i = 0 ; i < nb_pistons ; ++i) {
        if (anch_type == ENGINE_ALTERNATED_ALL || anch_type == ENGINE_ALTERNATED_RANDOM) {
            dir_anch_p = -dir_anch_p;
        }
        AnchorPoint anch_p(coords + dir_anch_p * offset_other_direction, dir_anch_p, pipe_width);
        coords = QVector3D(coords[0] + direction[0] * offset_piston, coords[1] + direction[1] * offset_piston, coords[2] + direction[2] * offset_piston);
        anch_points.push_back(anch_p);
    }

    anchor_points.push_back(anch_points);
}

void Engine::generateRules(QString engine_part) {
    set_rotation(engine_part);
    if (engine_part == "CubHeadEngine") {
        QVector3D center_cyl_head = center - direction * (pipe_length/2 + head_length/2);
        createLeafRulesSingle("cub", engine_part, QVector<float>({head_width*2, head_length, head_width*2}), center_cyl_head, rotation);
    }
    else if (engine_part == "CylHeadEngine") {
        QVector3D center_cyl_head = center - direction * (pipe_length/2 + head_length/2);
        createLeafRulesSingle("cyl", engine_part, QVector<float>({head_width, head_length, precision}), center_cyl_head, rotation);
    }
    else if (engine_part == "CylMainAxe") {
        float pipe_piece_length = pistons_gap;
        QVector<QString> primitives(nb_pistons*2+1, "cyl");
        QString op_bools(nb_pistons*2, '+');
        QVector<QVector<float>> params(nb_pistons*2+1, {pipe_width, pipe_piece_length+0.003f, precision});
        QVector<QVector3D> rots(nb_pistons*2+1, rotation);
        QVector<QVector3D> centers;

        QVector3D center_cyl_head = center - direction * (pipe_length/2 + head_length/2);
        QVector3D center(center_cyl_head + direction * (head_length/2 + pistons_gap/2));

        for (int i = 0 ; i < nb_pistons+1 ; ++i) {
            centers.push_back(center);
            center += direction * (pistons_gap * 2 + sep_length * 2);
        }

        //nécessite de créer tous les points d'ancrage au préalable
        for (int i = 0 ; i < anchor_points[0].size() ; ++i) {
            centers.push_back(anchor_points[0][i].coords);
        }

        QString rule = createLeafRulesMultiple(primitives, op_bools, params, centers, rots);
        rules.insert(engine_part, {rule});
    }
    else if (engine_part == "CubExtEngine") {
        QVector3D center_cyl_ext = center + direction * (pipe_length/2 + end_length/2);
        createLeafRulesSingle("cub", engine_part, QVector<float>({end_width, end_length, end_width}), center_cyl_ext, rotation);
    }
    else if (engine_part == "CylExtEngine") {
        QVector3D center_cyl_ext = center + direction * (pipe_length/2 + end_length/2);
        createLeafRulesSingle("cyl", engine_part, QVector<float>({end_width, end_length, precision}), center_cyl_ext, rotation);
    }


    else if (engine_part == "Aligned4All" || engine_part == "Aligned4Rand" || engine_part == "Alternated4All" || engine_part == "Alternated4Rand"
             || engine_part == "AlignedNRand" || engine_part == "AlternatedNRand" || engine_part == "AlignedNAll" || engine_part == "AlternatedNAll") {

        QString rule = "";
        QVector<AnchorPoint*> anch_p = choose_anchor_points();
        for (int i = 0 ; i < anch_p.size() ; ++i) {
            piston.sentence = piston.base_sentence;
            piston.set_prev_anchor_point(anch_p[i]);
            piston.set_center();

            for (int k = 0 ; k < piston.primitives_str.size() ; ++k) {
                piston.generateRules(piston.primitives_str.at(k));
            }
            piston.computeSentence();
            rule += piston.sentence;
            if (i != nb_pistons-1) {
                rule += "+";
            }
        }
        rules.insert(engine_part, {rule});
    }

    else if (engine_part == "CylSeparators") {
        QVector<QVector<float>> params;
        QVector<float> param({sep_width, sep_length, precision});
        QVector<QVector3D> centers;
        QVector<QVector3D> rots;
        QVector<QString> primitives;
        QString op_bools;

        QVector3D center_cyl_head = center - direction * (pipe_length/2 + head_length/2);
        float offset = pistons_gap + sep_length;
        QVector3D center = center_cyl_head + direction*(head_length/2 + pistons_gap + sep_length/2);
        params.push_back(param);
        centers.push_back(center);
        rots.push_back(rotation);
        primitives.push_back("cyl");
        for (int i = 0 ; i < nb_pistons*2-1 ; ++i) {
            params.push_back(param);
            center = QVector3D(center[0] + direction[0] * offset, center[1] + direction[1] * offset, center[2] + direction[2] * offset);
            centers.push_back(center);
            rots.push_back(rotation);
            primitives.push_back("cyl");
            op_bools += "+";
        }

        QString rule = createLeafRulesMultiple(primitives, op_bools, params, centers, rots);
        rules.insert(engine_part, {rule});
    }
    else if (engine_part == "CubSeparators") {

    }

}

QVector<AnchorPoint*> Engine::choose_anchor_points() {
    QVector<AnchorPoint*> res;
    if (anch_type == ENGINE_ALIGNED_ALL || anch_type == ENGINE_ALTERNATED_ALL) {
        for (int i = 0 ; i < anchor_points[0].size() ; ++i) {
            res.push_back(&anchor_points[0][i]);
        }
    }
    else if (anch_type == ENGINE_ALIGNED_RANDOM || anch_type == ENGINE_ALTERNATED_RANDOM) {
        for (int i = 0 ; i < anchor_points[0].size() ; ++i) {
            int rand = std::uniform_int_distribution<int>{0,1}(rd);
            if (rand == 0) {
                res.push_back(&anchor_points[0][i]);
            }
        }
    }
    return res;
}
