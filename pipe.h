#ifndef PIPE_H
#define PIPE_H

#include "generator.h"

class Pipe : public Generator
{
    float radius = -1;
    float length = -1;
    int precision = -1;
public:
    Pipe();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void generateRules(QString screw_part) override;
    void set_rotation(QString screw_part) override;
    void set_center() override;
    void set_anchor_points() override;
};

#endif // PIPE_H
