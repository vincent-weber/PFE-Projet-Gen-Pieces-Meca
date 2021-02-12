#ifndef MECHANICALPART_H
#define MECHANICALPART_H

#include <random>
#include "boolean_op.h"
#include "primitive.h"

class MechanicalPart
{
public:

    std::vector<Primitive*> shapes;
    std::vector<Bool_op> op_bool;

    Mesh_CGAL mesh;
    QVector<GLdouble> gl_data;
    int nb_vertices_gl_faces = 0;
    int nb_vertices_gl_lines = 0;

    MechanicalPart();
    MechanicalPart(std::vector<Primitive*> shapes, std::vector<Bool_op> op_bool);
    void render();

};

#endif // MECHANICALPART_H
