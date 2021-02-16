#ifndef MACHINERY_H
#define MACHINERY_H


#include <QVector3D>
#include "boolean_op.h"
#include "mechanicalpart.h"

class Machinery
{
public:

    Mesh_CGAL mesh;
    QVector<GLdouble> gl_data;
    int nb_vertices_gl_faces = 0;
    int nb_vertices_gl_lines = 0;
    Machinery();
    Machinery(MechanicalPart& part_lvl0, QVector<MechanicalPart> parts_lvl1);

    void add_new_parts(QVector<MechanicalPart> new_parts);
    void render();
};


#endif // MACHINERY_H
