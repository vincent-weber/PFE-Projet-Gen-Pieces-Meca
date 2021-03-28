#ifndef NUT_H
#define NUT_H

#include "generator.h"

/**
 * @brief The Screw class, représente les vis que l'on peut attacher sur les points d'ancrage. Cette pièce ne contient aucun point
 * d'ancrage, on ne peut rien attacher dessus.
 */
class Nut : public Generator
{
private:

    /**
     * @brief Tous les paramètre pour la création de la vis.
     */
    float main_cyl_radius = -1;
    float main_cyl_length = -1;
    int precision_main_cyl = -1;
    int precision_intersect_cyl = -1;
    float intersect_cyl_radius = -1;
public:
    Nut();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void generateRules(QString screw_part) override;
    void set_center() override;
    void set_rotation(QString screw_part) override;
    void set_anchor_points() override;
    QVector<AnchorPoint*> choose_anchor_points() override;

    /**
     * @brief set_main_cyl_radius permet de modifier la valeur du rayon du cylindre principal.
     * @param main_cyl_radius : la valeur souhaitée.
     */
    void set_main_cyl_radius(float main_cyl_radius) {
        this->main_cyl_radius = main_cyl_radius;
    }

    /**
     * @brief set_main_cyl_length permet de modifier la longueur du cylindre principal.
     * @param main_cyl_length : la valeur souhaitée.
     */
    void set_main_cyl_length(float main_cyl_length) {
        this->main_cyl_length = main_cyl_length;
    }

    /**
     * @brief set_inter_cyl_radius permet de modifier la valeur du rayon du cylindre qui coupe le cylindre principal.
     * @param inter_cyl_radius : la valeur souhaitée.
     */
    void set_inter_cyl_radius(float inter_cyl_radius){
        this->intersect_cyl_radius = inter_cyl_radius;
    }

    /**
     * @brief get_inter_cyl_rad
     * @return la valeur du rayon du cylindre qui coupe le cylindre principal.
     */
    float get_inter_cyl_rad() {return intersect_cyl_radius;}

};

#endif // NUT_H
