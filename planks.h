#ifndef PLANKS_H
#define PLANKS_H

#include "generator.h"

class Planks : public Generator
{
private:
    float dist_between_planks = -1;
    float planks_length = -1;
    float planks_height = -1;
    float planks_width = -1;

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
