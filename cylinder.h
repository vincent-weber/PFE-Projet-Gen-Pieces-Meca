#ifndef CYLINDER_H
#define CYLINDER_H

#include "primitive.h"

class Cylinder : public Primitive
{
public:

    float radius;
    float length;
    int precision;

    Cylinder(float radius, float length, int precision, V3 center = V3(0,0,0), V3 rotation = V3(0,0,0));
    Cylinder();
    void create_vertices() override;
    void create_mesh() override;
    void render() override;
};

#endif // CYLINDER_H
