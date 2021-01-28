#ifndef CYLINDER_H
#define CYLINDER_H

#include "shape3d.h"

class Cylinder : public Shape3D
{
public:

    float radius;
    float diameter;
    float precision;

    Cylinder(float radius, float diameter, float precision, V3 center = V3(0,0,0), V3 rotation = V3(0,0,0));
    Cylinder();
    void create_vertices() override;
    void create_mesh() override;
    void render() override;
};

#endif // CYLINDER_H
