#ifndef SPHERE_H
#define SPHERE_H

#include "shape3d.h"

class Sphere : public Shape3D
{
public:

    float radius;
    float stack_count;
    float sector_count;
    QVector<int> indices;

    Sphere();
    Sphere(float radius, float stack_count, float sector_count, V3 center = V3(0,0,0), V3 rotation = V3(0,0,0));

    void create_vertices() override;
    void create_mesh() override;
    void render() override;
};

#endif // SPHERE_H
