#ifndef SHAPE3D_H
#define SHAPE3D_H

#include "Cgal.h"
#include "util.h"
#include <QOpenGLFunctions>
#include <QDebug>

class Shape3D
{
public:

    V3 center;
    V3 rotation;

    std::vector<vertex_descriptor> v_handles;
    Mesh_CGAL mesh;

    QVector<GLdouble> gl_data;
    int nb_vertices_gl_faces = 0;
    int nb_vertices_gl_lines = 0;

    virtual void create();
    virtual void create_vertices() = 0;
    virtual void create_mesh() = 0;
    virtual void transform();
    virtual void render() = 0;
};

#endif // SHAPE3D_H
