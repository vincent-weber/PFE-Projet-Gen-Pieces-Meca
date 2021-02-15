#ifndef BOXGENERATOR_H
#define BOXGENERATOR_H

#include "generator.h"

class BoxGenerator : public Generator
{
private :
    float box_width = -1;
    float box_height = -1;
    float box_length = -1;
    float box_thickness = -1;

    float screws_width = -1;
    float screw_spot_thickness = -1;
    int screws_precision = -1;
public:
    BoxGenerator();
    std::random_device rd;
    void generate(QString screw_part) override;
    QString generate_top();
    QString generate_screws();
};

#endif // BOXGENERATOR_H
