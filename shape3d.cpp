#include "shape3d.h"

void Shape3D::create() {
    create_vertices();
    create_mesh();
    transform();
}

void Shape3D::transform() {
    //Rotation Y
    PMP::transform(CGAL::Aff_transformation_3<K>(cos(rotation[0]), 0, -sin(rotation[0]),
                                                0, 1, 0,
                                                sin(rotation[0]), 0, cos(rotation[0])), mesh);

    //Rotation Z
    PMP::transform(CGAL::Aff_transformation_3<K>(cos(rotation[1]), -sin(rotation[1]), 0,
                                                sin(rotation[1]), cos(rotation[1]), 0,
                                                0, 0, 1), mesh);

    PMP::transform(CGAL::Aff_transformation_3<K>(CGAL::Translation(), center), mesh);
}
