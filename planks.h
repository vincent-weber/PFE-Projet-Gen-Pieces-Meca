#ifndef PLANKS_H
#define PLANKS_H

#include "generator.h"
#include "hinge.h"
#include "screw.h"
#include "mechanicalpart.h"
#include "parser.h"

/**
 * @brief The Planks class Représente des planches légèrement espacées pouvant être reliées par des charnières (Hinge).
 * Pour l'instant, une seule implémentation, 5 planches en forme de croix avec une planche centrale, reliées par des charnières.
 * Il manque aussi l'ajout de vis aux emplacements des trous des charnières.
 *
 * max_size et min_size non utilisés.
 *
 * rules.insert("Planks", {"PlanksLayout+HingesLayout"});
   rules.insert("PlanksLayout", {"FlatLayout", "PerpendicularLayout"});
   rules.insert("HingesLayout", {"AllHinges", "RandomHinges"});

   PlanksLayout définit la façon dont sont agencées les planches. Seul FlatLayout est implémenté. PerpendicularLayout serait des planches
   perpendiculaires les unes par rapport aux autres, et utiliserait les charnières perpendiculaires (qui ne sont pas non plus implémentées).
   HingesLayout définit la manière dont les points d'ancrage seront sélectionnés (la création est pour le moment toujours la même).

   Points d'ancrage :

   PLANKS_ALL_HINGES : tous les points d'ancrage seront sélectionnés, donc toutes les charnières possibles seront présentes.
   PLANKS_RANDOM_HINGES : chaque point d'ancrage a une chance sur 2 d'être sélectionné.
 */
class Planks : public Generator
{
private:
    float dist_between_planks = -1;
    float planks_length = -1;
    float planks_height = -1;
    float planks_width = -1;

    float dist_between_hinges_length = -1;
    float dist_between_hinges_width = -1;
    float starting_offset = -1;

    int nb_anch_points_length = -1;
    int nb_anch_points_width = -1;
    float hinge_wing_height = -1;

    Hinge hinge;
    Screw screw;

    MechanicalPart base;
    QVector<MechanicalPart> parts;

public:
    Planks();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void set_center() override;
    void set_rotation(QString screw_part) override;
    void set_anchor_points() override;
    QVector<AnchorPoint*> choose_anchor_points() override;
    void generateRules(QString screw_part) override;

    MechanicalPart get_base() {
        return base;
    }

    QVector<MechanicalPart> get_parts() {
        return parts;
    }
};

#endif // PLANKS_H
