#include "primitive.h"

void Primitive::create() {
    create_vertices();
    create_mesh();
    transform();
}

void Primitive::transform() {
    double rotX = CGAL::to_double(rotation[0]);
    double rotY = CGAL::to_double(rotation[1]);
    double rotZ = CGAL::to_double(rotation[2]);

    //Rotation X
    PMP::transform(CGAL::Aff_transformation_3<K>(cos(rotX), -sin(rotX), 0,
                                                sin(rotX), cos(rotX), 0,
                                                0, 0, 1), mesh);

    //Rotation Y
    PMP::transform(CGAL::Aff_transformation_3<K>(cos(rotY), 0, -sin(rotY),
                                                0, 1, 0,
                                                sin(rotY), 0, cos(rotY)), mesh);

    //Rotation Z
    PMP::transform(CGAL::Aff_transformation_3<K>(cos(rotZ), -sin(rotZ), 0,
                                                sin(rotZ), cos(rotZ), 0,
                                                0, 0, 1), mesh);

    //Translation
    PMP::transform(CGAL::Aff_transformation_3<K>(CGAL::Translation(), center), mesh);
}
