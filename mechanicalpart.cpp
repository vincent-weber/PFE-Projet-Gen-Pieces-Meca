#include "mechanicalpart.h"

MechanicalPart::MechanicalPart() {}

MechanicalPart::MechanicalPart(std::vector<Shape3D*> shapes, std::vector<Bool_op> op_bool) : shapes(shapes), op_bool(op_bool)
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

void MechanicalPart::render() {
    std::random_device rd;
    float c1 = std::uniform_real_distribution<float>{0, 255}(rd);
    float c2 = std::uniform_real_distribution<float>{0, 255}(rd);
    int rand = std::uniform_int_distribution<int>{0, 2}(rd);
    for (face_descriptor& face : mesh.faces()) {
        CGAL::Vertex_around_face_iterator<Mesh_CGAL> vbegin, vend;
        for(boost::tie(vbegin, vend) = vertices_around_face(mesh.halfedge(face), mesh) ; vbegin != vend ; ++vbegin) {
            P3 p = mesh.point(*vbegin);
            gl_data.push_back(CGAL::to_double(p[0]));gl_data.push_back(CGAL::to_double(p[1]));gl_data.push_back(CGAL::to_double(p[2]));
            if (rand == 0) {
                gl_data.push_back(c1); gl_data.push_back(c2); gl_data.push_back(0.0);
            }
            else if (rand == 1) {
                gl_data.push_back(c1); gl_data.push_back(0); gl_data.push_back(c2);
            }
            else if (rand == 2) {
                gl_data.push_back(0); gl_data.push_back(c1); gl_data.push_back(c2);
            }

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
