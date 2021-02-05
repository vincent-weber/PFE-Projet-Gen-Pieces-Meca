 #ifndef SCREWGENERATOR_H
#define SCREWGENERATOR_H

#include "generator.h"

class ScrewGenerator : public Generator
{
public:
    ScrewGenerator();
    std::random_device rd;
    void generate(QString screw_part) override;

    float body_height = 0;
    float body_width = 0;
    float head_height = 0;
    float head_width = 0;
    int body_precision = 0;
};

#endif // SCREWGENERATOR_H
