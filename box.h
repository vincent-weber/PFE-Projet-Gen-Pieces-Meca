#ifndef BOX_H
#define BOX_H

#include "generator.h"
#include "screw.h"
#include "parser.h"
#include "mechanicalpart.h"

class Box : public Generator
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
    Box();
    std::random_device rd;
    void generate(QString screw_part) override;
    QString generate_top();
    QVector<MechanicalPart> generate_screws();
};

#endif // BOX_H
