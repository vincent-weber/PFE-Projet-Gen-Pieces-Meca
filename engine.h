#ifndef ENGINE_H
#define ENGINE_H

#include "generator.h"

class Engine : public Generator
{
private :
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

public:
    Engine();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void set_rotation(QString screw_part) override;
    void set_center() override;
    void generateRules(QString screw_part) override;
    void set_anchor_points() override;
    QVector<AnchorPoint> choose_anchor_points() override;
};

#endif // ENGINE_H
