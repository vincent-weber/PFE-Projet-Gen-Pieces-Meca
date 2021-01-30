#include "cylinder.h"

Cylinder::Cylinder()
{
}

Cylinder::Cylinder(float rad, float diam, float prec, V3 c, V3 rot) : radius(rad), length(diam), precision(prec) {
    center = c;
    rotation = rot;
    create_vertices();
    create_mesh();
    transform();
}

void Cylinder::create_vertices() {
    float angle_offset = 2*PI / precision;
    float angle = 0.0f;
    for (int i = 0 ; i < precision ; ++i, angle += angle_offset) {
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;
        P3 p1(x,y, -length/2);
        v_handles.push_back(mesh.add_vertex(p1));

        P3 p2(x,y, length/2);
        v_handles.push_back(mesh.add_vertex(p2));
    }
}

void Cylinder::create_mesh() {
    int nb_vertices = precision * 2;

    //Creation du mesh
    for (int i = 0 ; i < nb_vertices ; i += 2) {
        //facettes
        mesh.add_face(v_handles[i], v_handles[(i+2)%nb_vertices], v_handles[(i+1)%nb_vertices]);
        mesh.add_face(v_handles[(i+1)%nb_vertices], v_handles[(i+2)%nb_vertices], v_handles[(i+3)%nb_vertices]);

        //bouts du cylindre
        if ((i+2)%nb_vertices != 0 && (i+4)%nb_vertices != 0)
            mesh.add_face(v_handles[0], v_handles[(i+4)%nb_vertices], v_handles[(i+2)%nb_vertices]);
        if ((i+1)%nb_vertices != 1 && (i+3)%nb_vertices != 1)
            mesh.add_face(v_handles[1], v_handles[(i+1)%nb_vertices], v_handles[(i+3)%nb_vertices]);
    }
}

void Cylinder::render() {

    int nb_vertices = precision * 2;
    for (int i = 0 ; i < nb_vertices ; i += 2) {

        auto p0 = mesh.point(v_handles[0]);
        auto p1 = mesh.point(v_handles[1]);
        auto pi0 = mesh.point(v_handles[i]);
        auto pi1 = mesh.point(v_handles[(i+1)%nb_vertices]);
        auto pi2 = mesh.point(v_handles[(i+2)%nb_vertices]);
        auto pi3 = mesh.point(v_handles[(i+3)%nb_vertices]);
        auto pi4 = mesh.point(v_handles[(i+4)%nb_vertices]);

        gl_data.push_back(CGAL::to_double(pi1[0]));   gl_data.push_back(CGAL::to_double(pi1[1]));   gl_data.push_back(CGAL::to_double(pi1[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);
        gl_data.push_back(CGAL::to_double(pi0[0]));   gl_data.push_back(CGAL::to_double(pi0[1]));   gl_data.push_back(CGAL::to_double(pi0[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);
        gl_data.push_back(CGAL::to_double(pi2[0]));   gl_data.push_back(CGAL::to_double(pi2[1]));   gl_data.push_back(CGAL::to_double(pi2[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);

        gl_data.push_back(CGAL::to_double(pi3[0]));   gl_data.push_back(CGAL::to_double(pi3[1]));   gl_data.push_back(CGAL::to_double(pi3[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);
        gl_data.push_back(CGAL::to_double(pi1[0]));   gl_data.push_back(CGAL::to_double(pi1[1]));   gl_data.push_back(CGAL::to_double(pi1[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);
        gl_data.push_back(CGAL::to_double(pi2[0]));   gl_data.push_back(CGAL::to_double(pi2[1]));   gl_data.push_back(CGAL::to_double(pi2[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);

        gl_data.push_back(CGAL::to_double(pi2[0]));   gl_data.push_back(CGAL::to_double(pi2[1]));   gl_data.push_back(CGAL::to_double(pi2[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);
        gl_data.push_back(CGAL::to_double(p0[0]));    gl_data.push_back(CGAL::to_double(p0[1]));    gl_data.push_back(CGAL::to_double(p0[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);
        gl_data.push_back(CGAL::to_double(pi4[0]));   gl_data.push_back(CGAL::to_double(pi4[1]));   gl_data.push_back(CGAL::to_double(pi4[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);

        gl_data.push_back(CGAL::to_double(p1[0]));    gl_data.push_back(CGAL::to_double(p1[1]));    gl_data.push_back(CGAL::to_double(p1[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);
        gl_data.push_back(CGAL::to_double(pi1[0]));   gl_data.push_back(CGAL::to_double(pi1[1]));   gl_data.push_back(CGAL::to_double(pi1[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);
        gl_data.push_back(CGAL::to_double(pi3[0]));   gl_data.push_back(CGAL::to_double(pi3[1]));   gl_data.push_back(CGAL::to_double(pi3[2])); gl_data.push_back(0); gl_data.push_back(255); gl_data.push_back(255);
    }

    nb_vertices_gl_faces = 12 * precision;


    for (edge_descriptor ed : mesh.edges()) {
        P3 p1 = mesh.point(mesh.vertex(ed, 0));
        gl_data.push_back(CGAL::to_double(p1[0]));gl_data.push_back(CGAL::to_double(p1[1]));gl_data.push_back(CGAL::to_double(p1[2])); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        P3 p2 = mesh.point(mesh.vertex(ed, 1));
        gl_data.push_back(CGAL::to_double(p2[0]));gl_data.push_back(CGAL::to_double(p2[1]));gl_data.push_back(CGAL::to_double(p2[2])); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        nb_vertices_gl_lines += 2;
    }
}
