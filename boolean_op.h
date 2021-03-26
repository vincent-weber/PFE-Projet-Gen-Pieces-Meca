#ifndef BOOLEAN_OP_H
#define BOOLEAN_OP_H

#include "Cgal.h"
#include "QDebug"

enum Bool_op {
    UNION,
    INTERSECTION,
    DIFFERENCE
};

/**
 * @brief compute_boolean_operation op booléenne entre 2 maillages
 * @param in1 maillage d'entrée 1
 * @param in2 maillage d'entrée 2
 * @param out maillage de sortie
 * @param op_type type d'opération booléenne à effectuer
 * @return true ou false si l'opération a réussi ou pas
 */
bool compute_boolean_operation(Mesh_CGAL* in1, Mesh_CGAL* in2, Mesh_CGAL* out, Bool_op op_type);

#endif // BOOLEAN_OP_H
