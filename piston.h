#ifndef PISTON_H
#define PISTON_H

#include "generator.h"
#include "machinery.h"
#include "pipe.h"
#include "box.h"
#include "screw.h"

class Piston : public Generator
{
private:
    float head_height = -1;
    float head_width = -1;
    int head_precision = -1;

    float head_inter_width = -1;

    float body_height = -1;
    float body_width = -1;
    float body_length = -1;

    float endCyl_width = -1;
    float endCyl_height = -1;
    int endCyl_precision = -1;

    float endCyl_inter_width = -1;

public:
    Piston();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void generateRules(QString screw_part) override;
    void set_rotation(QString screw_part) override;
    void set_center() override;
    void set_anchor_points() override;
    QVector<AnchorPoint> choose_anchor_points() override;


};

#endif // PISTON_H
