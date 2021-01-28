#include "cuboid.h"

Cuboid::Cuboid()
{}

Cuboid::Cuboid(float l, float w, float h, V3 c, V3 r) : length(l), width(w), height(h) {
    center = c;
    rotation = r;
    create_vertices();
    create_mesh();
    transform();
}

void Cuboid::create_vertices() {
    v_handles.push_back(mesh.add_vertex(P3(-length, -height, -width)));
    v_handles.push_back(mesh.add_vertex(P3(-length, -height, width)));
    v_handles.push_back(mesh.add_vertex(P3(-length, height, -width)));
    v_handles.push_back(mesh.add_vertex(P3(-length, height, width)));
    v_handles.push_back(mesh.add_vertex(P3(length, -height, -width)));
    v_handles.push_back(mesh.add_vertex(P3(length, -height, width)));
    v_handles.push_back(mesh.add_vertex(P3(length, height, -width)));
    v_handles.push_back(mesh.add_vertex(P3(length, height, width)));
}

void Cuboid::create_mesh() {
    mesh.add_face(v_handles[0], v_handles[2], v_handles[1]); //-l
    mesh.add_face(v_handles[3], v_handles[1], v_handles[2]);
    mesh.add_face(v_handles[4], v_handles[5], v_handles[6]);//l
    mesh.add_face(v_handles[6], v_handles[5], v_handles[7]);
    mesh.add_face(v_handles[0], v_handles[1], v_handles[4]);//-h
    mesh.add_face(v_handles[4], v_handles[1], v_handles[5]);
    mesh.add_face(v_handles[3], v_handles[2], v_handles[6]);//h
    mesh.add_face(v_handles[3], v_handles[6], v_handles[7]);
    mesh.add_face(v_handles[2], v_handles[0], v_handles[4]);//-w
    mesh.add_face(v_handles[2], v_handles[4], v_handles[6]);
    mesh.add_face(v_handles[1], v_handles[3], v_handles[5]);//w
    mesh.add_face(v_handles[5], v_handles[3], v_handles[7]);
}

void Cuboid::render() {
    auto p0 = mesh.point(v_handles[0]);
    auto p1 = mesh.point(v_handles[1]);
    auto p2 = mesh.point(v_handles[2]);
    auto p3 = mesh.point(v_handles[3]);
    auto p4 = mesh.point(v_handles[4]);
    auto p5 = mesh.point(v_handles[5]);
    auto p6 = mesh.point(v_handles[6]);
    auto p7 = mesh.point(v_handles[7]);

    gl_data.push_back(p0[0]); gl_data.push_back(p0[1]); gl_data.push_back(p0[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//-l
    gl_data.push_back(p1[0]); gl_data.push_back(p1[1]); gl_data.push_back(p1[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p2[0]); gl_data.push_back(p2[1]); gl_data.push_back(p2[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p3[0]); gl_data.push_back(p3[1]); gl_data.push_back(p3[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p2[0]); gl_data.push_back(p2[1]); gl_data.push_back(p2[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p1[0]); gl_data.push_back(p1[1]); gl_data.push_back(p1[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    gl_data.push_back(p4[0]); gl_data.push_back(p4[1]); gl_data.push_back(p4[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//l
    gl_data.push_back(p6[0]); gl_data.push_back(p6[1]); gl_data.push_back(p6[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p5[0]); gl_data.push_back(p5[1]); gl_data.push_back(p5[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p6[0]); gl_data.push_back(p6[1]); gl_data.push_back(p6[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p7[0]); gl_data.push_back(p7[1]); gl_data.push_back(p7[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p5[0]); gl_data.push_back(p5[1]); gl_data.push_back(p5[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    gl_data.push_back(p0[0]); gl_data.push_back(p0[1]); gl_data.push_back(p0[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//-h
    gl_data.push_back(p4[0]); gl_data.push_back(p4[1]); gl_data.push_back(p4[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p1[0]); gl_data.push_back(p1[1]); gl_data.push_back(p1[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p4[0]); gl_data.push_back(p4[1]); gl_data.push_back(p4[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p5[0]); gl_data.push_back(p5[1]); gl_data.push_back(p5[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p1[0]); gl_data.push_back(p1[1]); gl_data.push_back(p1[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    gl_data.push_back(p3[0]); gl_data.push_back(p3[1]); gl_data.push_back(p3[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//h
    gl_data.push_back(p6[0]); gl_data.push_back(p6[1]); gl_data.push_back(p6[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p2[0]); gl_data.push_back(p2[1]); gl_data.push_back(p2[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p3[0]); gl_data.push_back(p3[1]); gl_data.push_back(p3[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p7[0]); gl_data.push_back(p7[1]); gl_data.push_back(p7[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p6[0]); gl_data.push_back(p6[1]); gl_data.push_back(p6[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    gl_data.push_back(p2[0]); gl_data.push_back(p2[1]); gl_data.push_back(p2[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//-w
    gl_data.push_back(p4[0]); gl_data.push_back(p4[1]); gl_data.push_back(p4[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p0[0]); gl_data.push_back(p0[1]); gl_data.push_back(p0[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p2[0]); gl_data.push_back(p2[1]); gl_data.push_back(p2[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p6[0]); gl_data.push_back(p6[1]); gl_data.push_back(p6[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p4[0]); gl_data.push_back(p4[1]); gl_data.push_back(p4[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    gl_data.push_back(p1[0]); gl_data.push_back(p1[1]); gl_data.push_back(p1[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//w
    gl_data.push_back(p5[0]); gl_data.push_back(p5[1]); gl_data.push_back(p5[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p3[0]); gl_data.push_back(p3[1]); gl_data.push_back(p3[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p5[0]); gl_data.push_back(p5[1]); gl_data.push_back(p5[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p7[0]); gl_data.push_back(p7[1]); gl_data.push_back(p7[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p3[0]); gl_data.push_back(p3[1]); gl_data.push_back(p3[2]); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    nb_vertices_gl_faces = 36;

    for (edge_descriptor ed : mesh.edges()) {
        P3 p1 = mesh.point(mesh.vertex(ed, 0));
        gl_data.push_back(p1[0]);gl_data.push_back(p1[1]);gl_data.push_back(p1[2]); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        P3 p2 = mesh.point(mesh.vertex(ed, 1));
        gl_data.push_back(p2[0]);gl_data.push_back(p2[1]);gl_data.push_back(p2[2]); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        nb_vertices_gl_lines += 2;
    }
}
