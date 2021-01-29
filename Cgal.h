#ifndef CGAL_H
#define CGAL_H

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/transform.h>
#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include <CGAL/Polygon_mesh_processing/repair.h>
#include <CGAL/Polygon_mesh_processing/internal/repair_extra.h>
#include <CGAL/Aff_transformation_3.h>
#include <CGAL/aff_transformation_tags.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Surface_mesh<K::Point_3> Mesh_CGAL;

typedef Mesh_CGAL::Vertex_index vertex_descriptor;
typedef Mesh_CGAL::Edge_index edge_descriptor;
typedef Mesh_CGAL::Face_index face_descriptor;
typedef Mesh_CGAL::Halfedge_index halfedge_descriptor;
typedef K::Point_3 P3;
typedef K::Vector_3 V3;

namespace PMP = CGAL::Polygon_mesh_processing;
namespace params = CGAL::Polygon_mesh_processing::parameters;
//namespace SM = CGAL::Surface_Mesh<K::Point_3>;

#endif // CGAL_H
