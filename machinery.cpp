#include "machinery.h"

Machinery::Machinery() {}

Machinery::Machinery(MechanicalPart& base_part, QVector<MechanicalPart> other_parts)
{
    mesh = base_part.mesh;
    for (int i = 0 ; i < other_parts.size() ; ++i) {
        bool res = compute_boolean_operation(&mesh, &other_parts[i].mesh, &mesh, UNION);
        if (res) {
            qDebug() << "Op Finale OK";
        }
        else {
            qDebug() << "Op Finale foiree";
        }
    }
}

void Machinery::add_new_parts(QVector<MechanicalPart> new_parts) {
    for (int i = 0 ; i < new_parts.size() ; ++i) {
        bool res = compute_boolean_operation(&mesh, &new_parts[i].mesh, &mesh, UNION);
        if (res) {
            qDebug() << "Op Finale OK";
        }
        else {
            qDebug() << "Op Finale foiree";
        }
    }
}

void Machinery::render() {

    qDebug() << "NB FACES : " << mesh.num_faces();
    qDebug() << "NB EDGES : " << mesh.num_edges();
    qDebug() << "NB VERTICES : " << mesh.num_vertices();

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
