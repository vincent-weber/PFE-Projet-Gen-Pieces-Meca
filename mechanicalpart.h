#ifndef MECHANICALPART_H
#define MECHANICALPART_H

#include <random>
#include <QVector3D>
#include "boolean_op.h"
#include "primitive.h"

/**
 * @brief The MechanicalPart class Classe qui créé le maillage pour une pièce mécanique. Appelé après le parsing de la phrase finale de la pièce.
 */
class MechanicalPart
{
public:

    /**
     * @brief shapes primitives de la pièce mécanique
     */
    std::vector<Primitive*> shapes;

    /**
     * @brief op_bool opérations booléennes à effectuer entre les primitives
     */
    std::vector<Bool_op> op_bool;


    QVector3D center;

    /**
     * @brief mesh le mesh final de la pièce
     */
    Mesh_CGAL mesh;

    /**
     * @brief gl_data données pour le rendu
     */
    QVector<GLdouble> gl_data;
    int nb_vertices_gl_faces = 0;
    int nb_vertices_gl_lines = 0;

    MechanicalPart();

    /**
     * @brief compute_mesh remplit mesh au fur et à mesure en faisant les opérations booléennes op_bools entre les maillages d'entrée meshes
     * @param meshes maillages d'entrée
     * @param op_bools opérations booléennes
     */
    void compute_mesh(std::vector<Mesh_CGAL>& meshes, std::vector<Bool_op>& op_bools);

    /**
     * @brief MechanicalPart Constructeur, créé la pièce mécanique et son maillage.
     * @param shapes les primitives
     * @param op_bool opérations booléennes
     */
    MechanicalPart(std::vector<Primitive*> shapes, std::vector<Bool_op> op_bool);

    /**
     * @brief render fait le rendu de la pièce
     */
    void render();

};

#endif // MECHANICALPART_H
