#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Cgal.h"
#include "util.h"
#include <QOpenGLFunctions>
#include <QDebug>

/**
 * @brief The Primitive class permet de décrire toutes les primitives de notre programme.
 */
class Primitive
{
public:

    /**
     * @brief Chacune des primitives possèdent un vecteur centre et un vecteur rotation.
     */
    V3 center;
    V3 rotation;

    /**
     * @brief v_handles est le tableau contenant les sommets d'une primitive.
     */
    std::vector<vertex_descriptor> v_handles;

    Mesh_CGAL mesh;

    /**
     * @brief gl_data est le tableau des données qui seront envoyé au VBO.
     */
    QVector<GLdouble> gl_data;
    int nb_vertices_gl_faces = 0;
    int nb_vertices_gl_lines = 0;

    virtual void create();

    /**
     * @brief create_vertices permet de créer les sommets d'une primitive.
     */
    virtual void create_vertices() = 0;

    /**
     * @brief create_mesh permet des créer le mesh avec les sommets pré-définis.
     */
    virtual void create_mesh() = 0;

    /**
     * @brief transform permet d'appliquer des rotations a une primitive.
     */
    virtual void transform();

    /**
     * @brief render permet de remplir le tableau gl_data.
     */
    virtual void render() = 0;
};

#endif // PRIMITIVE_H
