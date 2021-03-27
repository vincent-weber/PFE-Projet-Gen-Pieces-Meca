#ifndef BOX_H
#define BOX_H

#include "generator.h"
#include "screw.h"
#include "parser.h"
#include "mechanicalpart.h"

/**
 * @brief The Box pièce mécanique représentant une boîte sur laquelle on peut attacher d'autres objets.
 *
 * min_size : valeur minimale pour les 3 dimensions de la boîte
 * max_size : valeur maximale pour les 3 dimensions de la boîte
 *
 * 2 types de boîte :
 * - Boite représentée par un simple cuboide (Simple3x3Rand, Simple3x3Sym, LongOneFace)
 * - Boîte avec du relief sur les contours (Relief3x3Rand, Relief3x3Sym)
 *
 * Points d'ancrage possibles :
 *
 * BOX_GRID_3X3_SYMMETRIC :
 * set_anchor_points : génère les points d'ancrage sous la forme d'une grille 3x3
 * choose_anchor_points : sélectionne les points d'ancrage de manière symétrique par rapport au centre de la grille 3x3
 *
   BOX_GRID_3X3_RANDOM :
   set_anchor_points : génère les points d'ancrage sous la forme d'une grille 3x3
   choose_anchor_points : sélectionne un point d'ancrage aléatoirement par face

   BOX_ONE_FACE_ALIGNED :
   set_anchor_points : génère des points d'ancrage tous alignés sur une seule face de la boîte (toujours la même)
   BOX_ANGLES :
   set_anchor_points : génère des points d'ancrage dans les angles des faces haut et bas de la boîte
   choose_anchor_points : non implémenté

   BOX_EDGE : THOMAS REMPLIS CA STP

   Center : le centre de la boîte, pour le moment la boîte n'a pas vraiment été concue pour être attachée à d'autres objets,
   c'est pourquoi son centre est en 0,0,0 de base.

   La fonction set_rotation n'est pas renseignée, on ne peut pas faire de rotation sur cette pièce pour le moment (pas vraiment utile).

 */
class Box : public Generator
{
private :

    //paramètres de la boîte
    float box_width = -1;
    float box_height = -1;
    float box_length = -1;

    //épaisseur du relief de la boîte
    float box_thickness = -1;
public:
    Box();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void generateRules(QString screw_part) override;
    void set_rotation(QString screw_part) override;
    void set_center() override;
    void set_anchor_points() override;
    QVector<AnchorPoint*> choose_anchor_points() override;
};

#endif // BOX_H
