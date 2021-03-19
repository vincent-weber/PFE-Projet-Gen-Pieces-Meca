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
    void set_center() override;
    void set_rotation(QString screw_part) override;
    void set_anchor_points() override;
    QVector<AnchorPoint*> choose_anchor_points() override;

    void set_main_cyl_radius(float main_cyl_radius) {
        this->main_cyl_radius = main_cyl_radius;
    }

    void set_main_cyl_length(float main_cyl_length) {
        this->main_cyl_length = main_cyl_length;
    }

    void set_inter_cyl_radius(float inter_cyl_radius){
        this->intersect_cyl_radius = inter_cyl_radius;
    }

};

#endif // NUT_H
