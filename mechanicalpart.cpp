#include "mechanicalpart.h"

MechanicalPart::MechanicalPart() {}

MechanicalPart::MechanicalPart(std::vector<Primitive*> shapes, std::vector<Bool_op> op_bool, bool is_unique) : shapes(shapes), op_bool(op_bool), is_unique(is_unique)
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

    if(is_unique){
        copies.push_back(mesh);
    }
    //PMP::transform(CGAL::Aff_transformation_3<K>(CGAL::Translation(), V3(center[0], center[1], center[2])), mesh);
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
