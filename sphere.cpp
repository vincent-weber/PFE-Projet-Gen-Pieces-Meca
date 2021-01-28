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

    for(int j = 0; j <= stack_count; ++j, angle_phi -= step_stack){
        for(int i = 0; i <= sector_count; ++i, angle_teta += step_sector){
            x = radius * cosf(angle_phi) * cosf(angle_teta);
            y = radius * sinf(angle_phi);
            z = radius * cosf(angle_phi) * sinf(angle_teta);
            v_handles.push_back(mesh.add_vertex(P3(x,y,z)));
        }
    }
}

void Sphere::create_mesh() {

    int k1, k2;

    for(int i =0; i < stack_count; ++i){
        k1 = i * (sector_count+1);
        k2 = k1 + sector_count + 1;

        for(int j = 0; j < sector_count; ++j, ++k1, ++k2){
            if(i != 0){
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1+1);
            }
            if(i != (stack_count-1)){
                indices.push_back(k1+1);
                indices.push_back(k2);
                indices.push_back(k2+1);
            }
        }
    }

    nb_vertices_gl_faces = ((stack_count*2)-2)*sector_count*3;
    for(int i = 0; i < nb_vertices_gl_faces; i += 3){
        mesh.add_face(v_handles[indices[i]], v_handles[indices[(i+1)%nb_vertices_gl_faces]], v_handles[indices[(i+2)%nb_vertices_gl_faces]]);
    }
}

void Sphere::render() {
    //stockage pour le rendu
    for(int i = 0; i < nb_vertices_gl_faces; i += 3){
        auto p1 = mesh.point(v_handles[indices[i]]);
        auto p2 = mesh.point(v_handles[indices[(i+1)%nb_vertices_gl_faces]]);
        auto p3 = mesh.point(v_handles[indices[(i+2)%nb_vertices_gl_faces]]);

        gl_data.append(p2.x()); gl_data.append(p2.y()); gl_data.append(p2.z());
        gl_data.append(128); gl_data.append(128); gl_data.append(0);

        gl_data.append(p1.x()); gl_data.append(p1.y()); gl_data.append(p1.z());
        gl_data.append(128); gl_data.append(128); gl_data.append(0);

        gl_data.append(p3.x()); gl_data.append(p3.y()); gl_data.append(p3.z());
        gl_data.append(128); gl_data.append(128); gl_data.append(0);
    }

    for (edge_descriptor ed : mesh.edges()) {
        P3 p1 = mesh.point(mesh.vertex(ed, 0));
        gl_data.push_back(p1[0]);gl_data.push_back(p1[1]);gl_data.push_back(p1[2]); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        P3 p2 = mesh.point(mesh.vertex(ed, 1));
        gl_data.push_back(p2[0]);gl_data.push_back(p2[1]);gl_data.push_back(p2[2]); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        nb_vertices_gl_lines += 2;
    }
}
