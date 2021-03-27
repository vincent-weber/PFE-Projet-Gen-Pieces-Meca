#ifndef HINGE_H
#define HINGE_H

#include "generator.h"

class Hinge : public Generator
{
private:
    float middle_cyl_width = -1;
    float middle_cyl_length = -1;
    int middle_cyl_precision = -1;

    float wing_length = -1;
    float wing_height = -1;
    float wing_width = -1;

    bool is_rounded = false;
    float rounding_cyl_width = -1;
    float rounding_cyl_height = -1;
    float rounding_cyl_precision = -1;

    float hole_radius = -1;
    float nb_holes = -1;
    QVector3D dir_wings;
public:
    Hinge();
    std::random_device rd;
    void generateParams(QString screw_part) override;
    void set_center() override;
    void set_rotation(QString screw_part) override;
    void set_anchor_points() override;
    QVector<AnchorPoint*> choose_anchor_points() override;
    void generateRules(QString screw_part) override;

    void set_dir_wings();

    void set_middle_cyl_width(float val) {
        middle_cyl_width = val;
    }

    void set_wing_height(float val) {
        wing_height = val;
    }

    float get_hole_radius() {
        return hole_radius;
    }
};

#endif // HINGE_H
