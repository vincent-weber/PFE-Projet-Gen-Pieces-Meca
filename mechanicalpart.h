#ifndef MECHANICALPART_H
#define MECHANICALPART_H

#include <random>
#include <QVector3D>
#include "boolean_op.h"
#include "primitive.h"

class MechanicalPart
{
public:

    std::vector<Primitive*> shapes;
    std::vector<Bool_op> op_bool;
    QVector3D center;

    Mesh_CGAL mesh;
    QVector<Mesh_CGAL> copies;
    QVector<GLdouble> gl_data;
    int nb_vertices_gl_faces = 0;
    int nb_vertices_gl_lines = 0;

    bool is_unique;

    MechanicalPart();
    MechanicalPart(std::vector<Primitive*> shapes, std::vector<Bool_op> op_bool, bool is_unique = true);
    void render();
    void copy_mesh(QVector3D center, QVector3D rotation);

};

#endif // MECHANICALPART_H
