#ifndef BUTTERFLGENERATOR_H
#define BUTTERFLGENERATOR_H

#include "generator.h"

class ButterflyGenerator : public Generator
{
public:
    ButterflyGenerator();
    QVector3D body_pos;
    float body_rad;
    float body_len;
    float w;
};

#endif // BUTTERFLGENERATOR_H
