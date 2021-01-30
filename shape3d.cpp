#include "shape3d.h"

void Shape3D::create() {
    create_vertices();
    create_mesh();
    transform();
}

void Shape3D::transform() {
    //Rotation Y
    double rotY = CGAL::to_double(rotation[0]);
    double rotZ = CGAL::to_double(rotation[1]);
    PMP::transform(CGAL::Aff_transformation_3<K>(cos(rotY), 0, -sin(rotY),
                                                0, 1, 0,
                                                sin(rotY), 0, cos(rotY)), mesh);

    //Rotation Z
    PMP::transform(CGAL::Aff_transformation_3<K>(cos(rotZ), -sin(rotZ), 0,
                                                sin(rotZ), cos(rotZ), 0,
                                                0, 0, 1), mesh);

    PMP::transform(CGAL::Aff_transformation_3<K>(CGAL::Translation(), center), mesh);
}
