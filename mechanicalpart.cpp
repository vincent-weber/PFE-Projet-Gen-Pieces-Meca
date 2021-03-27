#include "mechanicalpart.h"

MechanicalPart::MechanicalPart() {}

void MechanicalPart::compute_mesh(std::vector<Mesh_CGAL>& meshes, std::vector<Bool_op>& op_bools) {
    mesh = meshes[0];
    for (unsigned i = 1 ; i < meshes.size() ; ++i) {
        bool res = compute_boolean_operation(&mesh, &meshes[i], &mesh, op_bools[i-1]);
        qDebug() << "OP CODE : " << op_bools[i-1];
        if (res) {
            qDebug() << "Op OK";
        }
        else {
            qDebug() << "Op foiree";
        }
    }
}

MechanicalPart::MechanicalPart(std::vector<Primitive*> shapes, std::vector<Bool_op> op_bool) : shapes(shapes), op_bool(op_bool)
{
    bool has_intersection = false;
    for (unsigned i = 0 ; i < op_bool.size() ; ++i) {
        if (op_bool[i] == INTERSECTION) {
            has_intersection = true;
        }
    }

    if (!has_intersection) {
        std::vector<Mesh_CGAL> meshes;
        for (unsigned i = 0 ; i < shapes.size() ; ++i) {
            meshes.push_back(shapes[i]->mesh);
        }
        compute_mesh(meshes, op_bool);
    }
    else {
        std::vector<Mesh_CGAL> meshes;
        std::vector<Bool_op> final_ops;

        for (unsigned i = 0 ; i < op_bool.size() ; ++i) {
            if (op_bool[i] != INTERSECTION) {
                if (i == 0 || (i > 0 && op_bool[i-1] != INTERSECTION)) {
                    meshes.push_back(shapes[i]->mesh);
                }
                final_ops.push_back(op_bool[i]);
                if (i == op_bool.size() - 1) {
                    meshes.push_back(shapes[i+1]->mesh);
                }
            }
            else {
                Mesh_CGAL mesh_intersection;
                bool res = compute_boolean_operation(&shapes[i]->mesh, &shapes[i+1]->mesh, &mesh_intersection, INTERSECTION);
                if (res) {
                    qDebug() << "Op Intersection OK";
                }
                else {
                    qDebug() << "Op Intersection foiree";
                }
                meshes.push_back(mesh_intersection);
            }
        }
        compute_mesh(meshes, final_ops);
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
