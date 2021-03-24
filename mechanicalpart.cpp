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

    if(is_unique){
        copies.push_back(mesh);
    }
}

MechanicalPart::MechanicalPart(std::vector<Primitive*> shapes, std::vector<Bool_op> op_bool, bool is_unique) : shapes(shapes), op_bool(op_bool), is_unique(is_unique)
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
    for(int i = 0; i < copies.size(); i++){
        float c1 = std::uniform_real_distribution<float>{0, 255}(rd);
        float c2 = std::uniform_real_distribution<float>{0, 255}(rd);
        int rand = std::uniform_int_distribution<int>{0, 2}(rd);
        for (face_descriptor& face : copies[i].faces()) {
            CGAL::Vertex_around_face_iterator<Mesh_CGAL> vbegin, vend;
            for(boost::tie(vbegin, vend) = vertices_around_face(copies[i].halfedge(face), copies[i]) ; vbegin != vend ; ++vbegin) {
                P3 p = copies[i].point(*vbegin);
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

        for (edge_descriptor ed : copies[i].edges()) {
            P3 p1 = copies[i].point(copies[i].vertex(ed, 0));
            gl_data.push_back(CGAL::to_double(p1[0]));gl_data.push_back(CGAL::to_double(p1[1]));gl_data.push_back(CGAL::to_double(p1[2])); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
            P3 p2 = copies[i].point(copies[i].vertex(ed, 1));
            gl_data.push_back(CGAL::to_double(p2[0]));gl_data.push_back(CGAL::to_double(p2[1]));gl_data.push_back(CGAL::to_double(p2[2])); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
            nb_vertices_gl_lines += 2;
        }
    }
}

void MechanicalPart::copy_mesh(QVector3D center, QVector3D rotation){
    Mesh_CGAL copy = mesh;



    double rotX = CGAL::to_double(rotation[0]);
    double rotY = CGAL::to_double(rotation[1]);
    double rotZ = CGAL::to_double(rotation[2]);

    //Rotation X
    PMP::transform(CGAL::Aff_transformation_3<K>(1, 0, 0,
                                                0, cos(rotX), -sin(rotX),
                                                0, sin(rotX), cos(rotX)), copy);

    //Rotation Y
    PMP::transform(CGAL::Aff_transformation_3<K>(cos(rotY), 0, -sin(rotY),
                                                0, 1, 0,
                                                sin(rotY), 0, cos(rotY)), copy);

    //Rotation Z
    PMP::transform(CGAL::Aff_transformation_3<K>(cos(rotZ), -sin(rotZ), 0,
                                                sin(rotZ), cos(rotZ), 0,
                                                0, 0, 1), copy);

    //Translation
    PMP::transform(CGAL::Aff_transformation_3<K>(CGAL::Translation(), V3(center[0], center[1], center[2])), copy);

    copies.push_back(copy);
}
