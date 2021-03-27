#ifndef MACHINERY_H
#define MACHINERY_H


#include <QVector3D>
#include "boolean_op.h"
#include "mechanicalpart.h"

/**
 * @brief The Machinery class Réalise l'union de plusieurs pièces mécaniques pour les fusionner en un seul maillage.
 */
class Machinery
{
public:

    /**
     * @brief mesh le mesh final
     */
    Mesh_CGAL mesh;

    /**
     * @brief gl_data données pour le rendu
     */
    QVector<GLdouble> gl_data;
    int nb_vertices_gl_faces = 0;
    int nb_vertices_gl_lines = 0;

    Machinery();

    /**
     * @brief Machinery constructeur, fusionne les pièces mécaniques en un seul maillage en réalisant l'union entre base_part et toutes les other_parts.
     * @param base_part la première pièce mécanique, sur laquelle réaliser toutes les unions.
     * @param other_parts les autres pièces à fusionner.
     */
    Machinery(MechanicalPart& base_part, QVector<MechanicalPart> other_parts);

    /**
     * @brief add_new_parts permet d'ajouter de nouvelles pièces mécaniques au mesh
     * @param new_parts les nouvelles parties
     */
    void add_new_parts(QVector<MechanicalPart> new_parts);

    /**
     * @brief render effectue le rendu
     */
    void render();
};


#endif // MACHINERY_H
