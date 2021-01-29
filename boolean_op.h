#ifndef BOOLEAN_OP_H
#define BOOLEAN_OP_H

#include "Cgal.h"
#include "QDebug"

enum Bool_op {
    UNION,
    INTERSECTION,
    DIFFERENCE
};

bool compute_boolean_operation(Mesh_CGAL* in1, Mesh_CGAL* in2, Mesh_CGAL* out, Bool_op op_type);

#endif // BOOLEAN_OP_H
