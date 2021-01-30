#include "sphere.h"

Sphere::Sphere()
{}

Sphere::Sphere(float rad, float stack_c, float sector_c, V3 c, V3 r) : radius(rad), stack_count(stack_c), sector_count(sector_c) {
    center = c;
    rotation = r;
    create_vertices();
    create_mesh();
    transform();
}

void Sphere::create_vertices() {
    float step_sector = 2*M_PI / sector_count;
    float step_stack = M_PI / stack_count;

    float angle_teta = 0;
    float angle_phi = M_PI/2;

    float x, y, z;

    for(int i = 0; i <= stack_count; ++i, angle_phi -= step_stack){
        for(int j = 0; j < sector_count; ++j, angle_teta += step_sector){
            x = radius * cosf(angle_phi) * cosf(angle_teta);
            y = radius * sinf(angle_phi);
            z = radius * cosf(angle_phi) * sinf(angle_teta);
            v_handles.push_back(mesh.add_vertex(P3(x,y,z)));
            if (i == 0 || i == stack_count) break;
        }
    }
}

void Sphere::create_mesh() {

    int k1, k2, b1, b2;
    for(int i =0; i < stack_count; ++i){
        b1 = (i-1)*(sector_count)+1;
        k1 = b1;
        b2 = k1 + sector_count;
        k2 = b2;
        for(int j = 0; j < sector_count; ++j, ++k1, ++k2){
            if (i == 0) {
                indices.push_back(0);
                indices.push_back(j+1);
                if (j != sector_count-1) {
                    indices.push_back(j+2);
                }
                else {
                    indices.push_back(1);
                }
                nb_vertices_gl_faces += 3;
            }
            else if (i == stack_count-1) {
                indices.push_back(k1);
                indices.push_back(v_handles.back());
                if (j != sector_count-1) {
                    indices.push_back(k1+1);
                }
                else {
                    indices.push_back(b1);
                }
                nb_vertices_gl_faces += 3;
            }

            else {
                indices.push_back(k1);
                indices.push_back(k2);
                if (j != sector_count-1) {
                    indices.push_back(k2+1);
                }
                else {
                    indices.push_back(b2);
                }

                indices.push_back(k1);
                if (j != sector_count-1) {
                    indices.push_back(k2+1);
                }
                else {
                    indices.push_back(b2);
                }

                if (j != sector_count-1) {
                    indices.push_back(k1+1);
                }
                else {
                    indices.push_back(b1);
                }
                nb_vertices_gl_faces += 6;
            }
        }
    }

    for(int i = 0; i < nb_vertices_gl_faces; i += 3){
        mesh.add_face(v_handles[indices[i]], v_handles[indices[(i+1)%nb_vertices_gl_faces]], v_handles[indices[(i+2)%nb_vertices_gl_faces]]);
    }
}

void Sphere::render() {
    for(int i = 0; i < nb_vertices_gl_faces; i += 3){
        auto p1 = mesh.point(v_handles[indices[i]]);
        auto p2 = mesh.point(v_handles[indices[(i+1)%nb_vertices_gl_faces]]);
        auto p3 = mesh.point(v_handles[indices[(i+2)%nb_vertices_gl_faces]]);

        gl_data.append(CGAL::to_double(p2[0])); gl_data.append(CGAL::to_double(p2[1])); gl_data.append(CGAL::to_double(p2[2]));
        gl_data.append(128); gl_data.append(128); gl_data.append(0);

        gl_data.append(CGAL::to_double(p1[0])); gl_data.append(CGAL::to_double(p1[1])); gl_data.append(CGAL::to_double(p1[2]));
        gl_data.append(128); gl_data.append(128); gl_data.append(0);

        gl_data.append(CGAL::to_double(p3[0])); gl_data.append(CGAL::to_double(p3[1])); gl_data.append(CGAL::to_double(p3[2]));
        gl_data.append(128); gl_data.append(128); gl_data.append(0);
    }

    for (edge_descriptor ed : mesh.edges()) {
        P3 p1 = mesh.point(mesh.vertex(ed, 0));
        gl_data.push_back(CGAL::to_double(p1[0]));gl_data.push_back(CGAL::to_double(p1[1]));gl_data.push_back(CGAL::to_double(p1[2])); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        P3 p2 = mesh.point(mesh.vertex(ed, 1));
        gl_data.push_back(CGAL::to_double(p2[0]));gl_data.push_back(CGAL::to_double(p2[1]));gl_data.push_back(CGAL::to_double(p2[2])); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        nb_vertices_gl_lines += 2;
    }
}
