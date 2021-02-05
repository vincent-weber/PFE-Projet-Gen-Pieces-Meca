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

    /*float body_radius = 0;
    float body_length = 0;
    int body_precision = 0;
    float head_radius = 0;
    float head_length= 0;
    int head_precision = 0;*/

    float body_height = 0;
    float body_width = 0;
    float head_height = 0;
    float head_width = 0;
    int body_precision = 0;
};

#endif // SCREWGENERATOR_H
