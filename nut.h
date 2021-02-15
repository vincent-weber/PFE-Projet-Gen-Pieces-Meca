#ifndef NUT_H
#define NUT_H

#include "generator.h"

class Nut : public Generator
{
private:
    float main_cyl_radius = -1;
    float main_cyl_length = -1;
    int precision_main_cyl = -1;
    int precision_intersect_cyl = -1;
    float intersect_cyl_radius = -1;
public:
    Nut();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void generateRules(QString screw_part) override;
    void set_center(AnchorPoint anchor_point) override;
    void set_rotation(QVector3D direction, QString screw_part) override;

    void set_main_cyl_radius(float main_cyl_radius) {
        this->main_cyl_radius = main_cyl_radius;
    }

    void set_main_cyl_length(float main_cyl_length) {
        this->main_cyl_length = main_cyl_length;
    }

};

#endif // NUT_H
