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
    auto p0 = mesh.point(v_handles[0]); double p00 = CGAL::to_double(p0[0]); double p01 = CGAL::to_double(p0[1]); double p02 = CGAL::to_double(p0[2]);
    auto p1 = mesh.point(v_handles[1]); double p10 = CGAL::to_double(p1[0]); double p11 = CGAL::to_double(p1[1]); double p12 = CGAL::to_double(p1[2]);
    auto p2 = mesh.point(v_handles[2]); double p20 = CGAL::to_double(p2[0]); double p21 = CGAL::to_double(p2[1]); double p22 = CGAL::to_double(p2[2]);
    auto p3 = mesh.point(v_handles[3]); double p30 = CGAL::to_double(p3[0]); double p31 = CGAL::to_double(p3[1]); double p32 = CGAL::to_double(p3[2]);
    auto p4 = mesh.point(v_handles[4]); double p40 = CGAL::to_double(p4[0]); double p41 = CGAL::to_double(p4[1]); double p42 = CGAL::to_double(p4[2]);
    auto p5 = mesh.point(v_handles[5]); double p50 = CGAL::to_double(p5[0]); double p51 = CGAL::to_double(p5[1]); double p52 = CGAL::to_double(p5[2]);
    auto p6 = mesh.point(v_handles[6]); double p60 = CGAL::to_double(p6[0]); double p61 = CGAL::to_double(p6[1]); double p62 = CGAL::to_double(p6[2]);
    auto p7 = mesh.point(v_handles[7]); double p70 = CGAL::to_double(p7[0]); double p71 = CGAL::to_double(p7[1]); double p72 = CGAL::to_double(p7[2]);

    gl_data.push_back(p00); gl_data.push_back(p01); gl_data.push_back(p02); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//-l
    gl_data.push_back(p10); gl_data.push_back(p11); gl_data.push_back(p12); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p20); gl_data.push_back(p21); gl_data.push_back(p22); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p30); gl_data.push_back(p31); gl_data.push_back(p32); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p20); gl_data.push_back(p21); gl_data.push_back(p22); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p10); gl_data.push_back(p11); gl_data.push_back(p12); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    gl_data.push_back(p40); gl_data.push_back(p41); gl_data.push_back(p42); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//l
    gl_data.push_back(p60); gl_data.push_back(p61); gl_data.push_back(p62); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p50); gl_data.push_back(p51); gl_data.push_back(p52); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p60); gl_data.push_back(p61); gl_data.push_back(p62); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p70); gl_data.push_back(p71); gl_data.push_back(p72); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p50); gl_data.push_back(p51); gl_data.push_back(p52); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    gl_data.push_back(p00); gl_data.push_back(p01); gl_data.push_back(p02); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//-h
    gl_data.push_back(p40); gl_data.push_back(p41); gl_data.push_back(p42); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p10); gl_data.push_back(p11); gl_data.push_back(p12); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p40); gl_data.push_back(p41); gl_data.push_back(p42); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p50); gl_data.push_back(p51); gl_data.push_back(p52); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p10); gl_data.push_back(p11); gl_data.push_back(p12); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    gl_data.push_back(p30); gl_data.push_back(p31); gl_data.push_back(p32); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//h
    gl_data.push_back(p60); gl_data.push_back(p61); gl_data.push_back(p62); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p20); gl_data.push_back(p21); gl_data.push_back(p22); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p30); gl_data.push_back(p31); gl_data.push_back(p32); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p70); gl_data.push_back(p71); gl_data.push_back(p72); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p60); gl_data.push_back(p61); gl_data.push_back(p62); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    gl_data.push_back(p20); gl_data.push_back(p21); gl_data.push_back(p22); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//-w
    gl_data.push_back(p40); gl_data.push_back(p41); gl_data.push_back(p42); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p00); gl_data.push_back(p01); gl_data.push_back(p02); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p20); gl_data.push_back(p21); gl_data.push_back(p22); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p60); gl_data.push_back(p61); gl_data.push_back(p62); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p40); gl_data.push_back(p41); gl_data.push_back(p42); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    gl_data.push_back(p10); gl_data.push_back(p11); gl_data.push_back(p12); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);//w
    gl_data.push_back(p50); gl_data.push_back(p51); gl_data.push_back(p52); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p30); gl_data.push_back(p31); gl_data.push_back(p32); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p50); gl_data.push_back(p51); gl_data.push_back(p52); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p70); gl_data.push_back(p71); gl_data.push_back(p72); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);
    gl_data.push_back(p30); gl_data.push_back(p31); gl_data.push_back(p32); gl_data.push_back(255); gl_data.push_back(0); gl_data.push_back(255);

    nb_vertices_gl_faces = 36;

    for (edge_descriptor ed : mesh.edges()) {
        P3 p1 = mesh.point(mesh.vertex(ed, 0));
        gl_data.push_back(p10);gl_data.push_back(p11);gl_data.push_back(p12); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        P3 p2 = mesh.point(mesh.vertex(ed, 1));
        gl_data.push_back(p20);gl_data.push_back(p21);gl_data.push_back(p22); gl_data.push_back(0); gl_data.push_back(0); gl_data.push_back(0);
        nb_vertices_gl_lines += 2;
    }
}
