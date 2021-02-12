#ifndef NUT_H
#define NUT_H

#include "generator.h"

class Nut : public Generator
{
private:
    float main_cyl_radius = -1;
    float main_cyl_length = -1;
public:
    Nut();
    std::random_device rd;
    void generate(QString screw_part) override;

    void set_main_cyl_radius(float main_cyl_radius) {
        this->main_cyl_radius = main_cyl_radius;
    }

    void set_main_cyl_length(float main_cyl_length) {
        this->main_cyl_length = main_cyl_length;
    }

};

#endif // NUT_H
