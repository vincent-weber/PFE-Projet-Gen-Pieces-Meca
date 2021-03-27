#ifndef ANCHORPOINT_H
#define ANCHORPOINT_H

#include <QVector3D>

//pour la compilation
class Generator;

/**
 * @brief The AnchorPoint class encapsule les informations pour les points d'ancrage
 */
class AnchorPoint
{
public:

    /**
     * @brief coords coordonnées du point d'ancrage dans l'espace global
     */
    QVector3D coords;

    /**
     * @brief direction la direction à donner à l'objet qui sera attaché à ce point d'ancrage
     */
    QVector3D direction;

    /**
     * @brief max_accepted_size taille maximale supportée par le point d'ancrage, pour ne pas
     * que l'objet attaché soit d'une taille disproportionnée
     */
    float max_accepted_size;

    /**
     * @brief is_active inutilisé
     */
    bool is_active = false;

    /**
     * @brief owner_object inutilisé, l'idée était de savoir pour un objet de connaître le type de celui
     * sur lequel il est attaché, pour peut-être l'évitement d'intersections entre objet.
     */
    Generator* owner_object;

    /**
     * @brief attached_object inutilisé aussi
     */
    Generator* attached_object;

    AnchorPoint();
    AnchorPoint(QVector3D coords, QVector3D direction, float max_accepted_size);
};

#endif // ANCHORPOINT_H
