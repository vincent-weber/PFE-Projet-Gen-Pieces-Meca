#ifndef CYLINDER_H
#define CYLINDER_H

#include "primitive.h"

/**
 * @brief The Cylinder class, cette classe permet de généner un cylindre.
 */
class Cylinder : public Primitive
{
public:

    /**
     * @brief radius, length, precision les paramètres nécessaire à la création d'un cylindre.
     */
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
