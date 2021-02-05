#ifndef NUTGENERATOR_H
#define NUTGENERATOR_H

#include "generator.h"

class NutGenerator : public Generator
{
public:
    NutGenerator();
    std::random_device rd;
    void generate(QString screw_part) override;

    float main_cyl_radius = 0;
    float main_cyl_length = 0;
};

#endif // NUTGENERATOR_H
