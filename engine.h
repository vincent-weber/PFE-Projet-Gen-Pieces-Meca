#ifndef ENGINE_H
#define ENGINE_H

#include "generator.h"

class Engine : public Generator
{
private :
    float pipe_length = -1;
    int nb_pistons = -1;

public:
    Engine();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void generateRules(QString screw_part) override;
    void set_rotation(QString screw_part) override;
    void set_center() override;
    void set_anchor_points() override;
    QVector<AnchorPoint> choose_anchor_points() override;
};

#endif // ENGINE_H
