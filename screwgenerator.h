#ifndef SCREWGENERATOR_H
#define SCREWGENERATOR_H

#include "generator.h"

class ScrewGenerator : public Generator
{
public:
    ScrewGenerator();
    std::random_device rd;
    void createRules() override;
    void generate(QString screw_part) override;
};

#endif // SCREWGENERATOR_H
