#ifndef CUBOID_H
#define CUBOID_H

#include "primitive.h"

/**
 * @brief The Cylinder class, cette classe permet de généner un cylindre.
 */
class Cuboid : public Primitive
{
public:

    /**
     * @brief length, width, height les paramètres nécessaire à la création d'un cuboid.
     */
    float length;
    float width;
    float height;

    Cuboid();
    Cuboid(float length, float height, float width, V3 center = V3(0,0,0), V3 rotation = V3(0,0,0));
    void create_vertices() override;
    void create_mesh() override;
    void render() override;
};

#endif // CUBOID_H
