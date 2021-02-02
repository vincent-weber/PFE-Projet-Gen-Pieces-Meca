#include "boolean_op.h"

bool compute_boolean_operation(Mesh_CGAL* in1, Mesh_CGAL* in2, Mesh_CGAL* out, Bool_op op_type) {

    //TODO : code de debug a separer
//    bool self_inter_in1 = PMP::does_self_intersect(*in1);
//    bool self_inter_in2 = PMP::does_self_intersect(*in2);
//    bool bound_volume_in1 = PMP::does_bound_a_volume(*in1);
//    bool bound_volume_in2 = PMP::does_bound_a_volume(*in2);
    PMP::orient_to_bound_a_volume(*in1);
    PMP::orient_to_bound_a_volume(*in2);
//    bool bound_volume_in3 = PMP::does_bound_a_volume(*in1);
//    bool bound_volume_in4 = PMP::does_bound_a_volume(*in2);

//    qDebug() << "SELF INTERSECT IN1 ? " << self_inter_in1;
//    qDebug() << "SELF INTERSECT IN2 ? " << self_inter_in2;
//    qDebug() << "BOUNDS A VOLUME IN1 AVANT ORIENT ? " << bound_volume_in1;
//    qDebug() << "BOUNDS A VOLUME IN2 AVANT ORIENT ? " << bound_volume_in2;
//    qDebug() << "BOUNDS A VOLUME IN1 APRES ORIENT ? " << bound_volume_in3;
//    qDebug() << "BOUNDS A VOLUME IN2 APRES ORIENT ? " << bound_volume_in4;
//    qDebug() << "NB VERT IN1 : " << in1->num_vertices();
//    qDebug() << "NB VERT IN2 : " << in2->num_vertices();

    bool valid_op = false;
    switch(op_type) {
    case UNION:
    {
        valid_op = PMP::corefine_and_compute_union(*in1, *in2, *out, params::throw_on_self_intersection(false));
        break;
    }
    case INTERSECTION:
    {
        valid_op = PMP::corefine_and_compute_intersection(*in1, *in2, *out, params::throw_on_self_intersection(false));
        break;
    }
    case DIFFERENCE:
    {
        valid_op = PMP::corefine_and_compute_difference(*in1, *in2, *out, params::throw_on_self_intersection(false));
        break;
    }
    }

    //TODO : code de debug a separer
    /*bool self_inter_out = PMP::does_self_intersect(*out);
    qDebug() << "SELF INTERSECT OUT ? " << self_inter_out;*/

    return valid_op;
}
