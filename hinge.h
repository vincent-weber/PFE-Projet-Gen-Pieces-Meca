#ifndef HINGE_H
#define HINGE_H

#include "generator.h"

/**
 * @brief The Hinge class Une charnière sur laquelle on peut insérer des vis.
 * Composé d'un axe central (HingeMiddleCyl), de 2 côtés (HingeWings) et de trous pour vis (HingeHolePattern)
 *
 * max_size : longueur maximale de l'axe central
 * min_size : longueur minimale de l'axe central
 *
 * rules.insert("Hinge", {"HingeMiddleCyl+HingeWings-HingeHolePattern"});
   rules.insert("HingeWings", {"AlignedSquared", "AlignedRounded", "PerpendicularSquared", "PerpendicularRounded"});
   rules.insert("HingeHolePattern", {"Random4Max", "RandomN", "Angles", "3x3Grid"});

   AlignedSquared et AlignedRounded correspondent à des charnières dont les 2 côtés (wings) sont dans la même direction.
   PerpendicularSquared et PerpendicularRounded ne sont pas implémentés, ce seraient des charnières telles que les 2 côtés sont perpendiculaires entre eux.

   Dans l'implémentation actuelle, les charnières alignées ne peuvent pas être tournées dans tous les sens (que les 2 directions utilisées dans la classe Planks).

   Points d'ancrage :

   HINGE_ANGLES_4 : non implémenté
   HINGE_GRID_3X3 : non implémenté, points d'ancrage en forme de grille 3x3 sur chaque côté = 18 trous en tout par charnière
   HINGE_RANDOM_4_MAX : le seul implémenté, créé 4 points d'ancrage maximale de manière aléatoire sur un côté et sur l'autre de manière symétrique.
   L'implémentation pourrait mieux fonctionner, surtout pour les charnières arrondies.
 */
class Hinge : public Generator
{
private:
    float middle_cyl_width = -1;
    float middle_cyl_length = -1;
    int middle_cyl_precision = -1;

    float wing_length = -1;
    float wing_height = -1;
    float wing_width = -1;

    bool is_rounded = false;
    float rounding_cyl_width = -1;
    float rounding_cyl_height = -1;
    float rounding_cyl_precision = -1;

    float hole_radius = -1;
    float nb_holes = -1;
    QVector3D dir_wings;
public:
    Hinge();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void set_center() override;
    void set_rotation(QString screw_part) override;
    void set_anchor_points() override;
    QVector<AnchorPoint*> choose_anchor_points() override;
    void generateRules(QString screw_part) override;

    void set_dir_wings();

    void set_middle_cyl_width(float val) {
        middle_cyl_width = val;
    }

    void set_wing_height(float val) {
        wing_height = val;
    }

    float get_hole_radius() {
        return hole_radius;
    }

    float get_middle_cyl_height() {
        return middle_cyl_length;
    }
};

#endif // HINGE_H
