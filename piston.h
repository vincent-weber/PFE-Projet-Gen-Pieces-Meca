#ifndef PISTON_H
#define PISTON_H

#include "generator.h"

#include "pipe.h"
#include "box.h"
#include "screw.h"

class Piston : public Generator
{
public:
    Piston();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void generateRules(QString screw_part) override;
    void set_rotation(QString screw_part) override;
    void set_center() override;
    void set_anchor_points() override;

    QStringList piston_str;


    QVector<Generator*> parts_generators;
};

#endif // PISTON_H
