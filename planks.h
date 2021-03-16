#ifndef PLANKS_H
#define PLANKS_H

#include "generator.h"
#include "hinge.h"

class Planks : public Generator
{
private:
    float dist_between_planks = -1;
    float planks_length = -1;
    float planks_height = -1;
    float planks_width = -1;

    float min_dist_between_hinges = 2.0f;

    int nb_anch_points_length = -1;
    int nb_anch_points_width = -1;
    float hinge_wing_height = -1;

    Hinge hinge;

public:
    Planks();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void set_center() override;
    void set_rotation(QString screw_part) override;
    void set_anchor_points() override;
    QVector<AnchorPoint*> choose_anchor_points() override;
    void generateRules(QString screw_part) override;
};

#endif // PLANKS_H