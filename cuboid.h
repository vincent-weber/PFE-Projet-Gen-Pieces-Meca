#ifndef CUBOID_H
#define CUBOID_H

#include "shape3d.h"

class Cuboid : public Shape3D
{
public:

    float length;
    float width;
    float height;

    Cuboid();
    Cuboid(float length, float width, float height, V3 center = V3(0,0,0), V3 rotation = V3(0,0,0));
    void create_vertices() override;
    void create_mesh() override;
    void render() override;
};

#endif // CUBOID_H
