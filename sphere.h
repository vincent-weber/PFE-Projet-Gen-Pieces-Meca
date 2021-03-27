#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

/**
 * @brief The Cylinder class, cette classe permet de généner un cylindre.
 */
class Sphere : public Primitive
{
public:

    /**
     * @brief radius, stack_count, sector_count, indices les parametres nécessaire à la création de la sphère.
     */
    float radius;
    int stack_count;
    int sector_count;
    QVector<int> indices;

    Sphere();
    Sphere(float radius, float stack_count, float sector_count, V3 center = V3(0,0,0), V3 rotation = V3(0,0,0));

    void create_vertices() override;
    void create_mesh() override;
    void render() override;
};

#endif // SPHERE_H
