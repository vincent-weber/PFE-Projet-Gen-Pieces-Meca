#ifndef SCREW_H
#define SCREW_H

#include "boolean_op.h"
#include "shape3d.h"

class Screw
{
public:

    std::vector<Shape3D*> shapes;
    std::vector<Bool_op> op_bool;

    Mesh_CGAL mesh;
    QVector<GLdouble> gl_data;
    int nb_vertices_gl_faces = 0;
    int nb_vertices_gl_lines = 0;

    Screw();
    Screw(std::vector<Shape3D*> shapes, std::vector<Bool_op> op_bool);
    void render();

};

#endif // SCREW_H
