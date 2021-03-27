#ifndef ENGINE_H
#define ENGINE_H

#include "generator.h"
#include "piston.h"

/**
 * @brief The Engine class Pièce mécanique représentant un moteur sur lequel on peut attacher des pistons.
 * Composé d'un axe moteur (EngineAxis), de séparateurs pour les pistons (SeparatorPistons) et de groupes de pistons (GroupPistons)
 *
 * max_size : la taille maximale de HeadEngine
 * min_size : la taille minimale de HeadEngine
 *
 * rules.insert("Engine", {"EngineAxis+GroupPistons+SeparatorPistons"});
   rules.insert("EngineAxis", {"CylHeadEngine+CylMainAxe+CylExtEngine", "CubHeadEngine+CylMainAxe+CubExtEngine"});
   rules.insert("GroupPistons", {"Aligned4All", "Aligned4Rand", "Alternated4All", "Alternated4Rand", "AlignedNRand", "AlternatedNRand", "AlignedNAll", "AlternatedNAll"});
   rules.insert("SeparatorPistons", {"CylSeparators", "CubSeparators"});

   CubSeparators non implémenté

   Pour les GroupPistons :
   Aligned : les pistons seront tous du même côté du moteur
   4, N : nombre d'emplacements pour les pistons sur le moteur
   All, Rand : S'il faut générer tous les pistons ou un nombre aléatoire parmi les emplacements possibles.

   Points d'ancrage possibles :

   ENGINE_ALIGNED_ALL :
   ENGINE_ALTERNATED_ALL
   ENGINE_ALIGNED_RANDOM
   ENGINE_ALTERNATED_RANDOM

   set_anchor_points : génère les points d'ancrage sur l'axe entre les séparateurs. Leur direction est la même si anch_type contient ALIGNED
   et de direction alternée une fois sur 2 si anch_type est ALTERNATED.
   choose_anchor_points : sélectionne tous les points d'ancrage (ENGINE_ALIGNED_ALL et ENGINE_ALTERNATED_ALL) ou seulement certains
   (ENGINE_ALIGNED_RANDOM et ENGINE_ALTERNATED_RANDOM)
 *
 */
class Engine : public Generator
{
private :
    const float pipe_length_min = 3.0f;
    const float pipe_length_max = 12.0f;

    float head_width = -1;
    float head_length = -1;
    float pipe_width = -1;
    float pipe_length = -1;
    float end_width = -1;
    float end_length = -1;
    float sep_width = -1;
    float sep_length = -1;
    int nb_pistons = -1;
    float piston_end_length = -1;
    float pistons_gap = -1;

    float precision = 16;

    Piston piston;

public:
    Engine();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void set_rotation(QString screw_part) override;
    void set_center() override;
    void generateRules(QString screw_part) override;
    void set_anchor_points() override;
    QVector<AnchorPoint*> choose_anchor_points() override;
};

#endif // ENGINE_H
