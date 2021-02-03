#include "screw.h"

Screw::Screw() {}

Screw::Screw(std::vector<Shape3D*> shapes, std::vector<Bool_op> op_bool) : shapes(shapes), op_bool(op_bool)
{
    mesh = shapes[0]->mesh;
    for (unsigned i = 1 ; i < shapes.size() ; ++i) {
        bool res = compute_boolean_operation(&mesh, &shapes[i]->mesh, &mesh, op_bool[i-1]);
        qDebug() << op_bool[i-1];
        if (res) {
            qDebug() << "Op OK";
        }
        else {
            qDebug() << "Op foiree";
        }
    }
}

void Screw::render() {
    for (face_descriptor& face : mesh.faces()) {
        CGAL::Vertex_around_face_iterator<Mesh_CGAL> vbegin, vend;
        for(boost::tie(vbegin, vend) = vertices_around_face(mesh.halfedge(face), mesh) ; vbegin != vend ; ++vbegin) {
            P3 p = mesh.point(*vbegin);
            gl_data.push_back(CGAL::to_double(p[0]));gl_data.push_back(CGAL::to_double(p[1]));gl_data.push_back(CGAL::to_double(p[2]));
            gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(0);
            ++nb_vertices_gl_faces;
        }
    }

    for (edge_descriptor ed : mesh.edges()) {
        P3 p1 = mesh.point(mesh.vertex(ed, 0));
        gl_data.push_back(CGAL::to_double(p1[0]));gl_data.push_back(CGAL::to_double(p1[1]));gl_data.push_back(CGAL::to_double(p1[2])); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        P3 p2 = mesh.point(mesh.vertex(ed, 1));
        gl_data.push_back(CGAL::to_double(p2[0]));gl_data.push_back(CGAL::to_double(p2[1]));gl_data.push_back(CGAL::to_double(p2[2])); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        nb_vertices_gl_lines += 2;
    }
}
