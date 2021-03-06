#include <math.h>
#include "geometry.hpp"
#include "constant.hpp"
#include "utils.hpp"
#include "objloader.hpp"


/**
 * Geometry class
 */

void Geometry::setMaterial(BRDF* new_mat)
{
    material = new_mat;
}


/**
 * Parallelogram class
 */

Parallelogram::Parallelogram(Eigen::Vector3f p0, Eigen::Vector3f s0, Eigen::Vector3f s1, Eigen::Vector3f normal, BRDF* mat)
    : p0(p0)
    , normal(normal.normalized())
{
    s0_len = s0.norm();
    s1_len = s1.norm();
    this->s0 = s0.normalized();
    this->s1 = s1.normalized();

    setMaterial(mat);
    buildBoundingBox();
}

bool Parallelogram::rayIntersection(Interaction& interaction, const Ray& ray)
{
    if (ray.direction.dot(normal) == 0)
    {
        return false;
    }
    
    float t = (p0 - ray.origin).dot(normal) / ray.direction.dot(normal);
    Eigen::Vector3f p0_p = ray.getPoint(t) - p0;
    float q0 = p0_p.dot(s0) / s0_len;
    float q1 = p0_p.dot(s1) / s1_len;
    if (q0 >= 0 && q0 <= s0.norm() && q1 >= 0 && q1 <= s1.norm() && t >= ray.range_min && t <= ray.range_max)
    {
        interaction.entry_dist = t;
        interaction.exit_dist = t;
        interaction.normal = normal;
        interaction.entry_point = ray.getPoint(t);
        if (material != nullptr)
        {
            interaction.material = (void*)material;
        }
        interaction.type = Interaction::Type::GEOMETRY;
        return true;
    }
    return false;
}

void Parallelogram::buildBoundingBox()
{
    Eigen::Vector3f p1 = p0 + s0 + s1;
    bounding_box.lb = p0.cwiseMin(p1);
    bounding_box.ub = p0.cwiseMax(p1);
}


/**
 * Sphere class
 */

Sphere::Sphere(Eigen::Vector3f p0, float r, BRDF* mat)
    : p0(p0)
    , radius(r)
{
    setMaterial(mat);
    buildBoundingBox();
}

bool Sphere::rayIntersection(Interaction& interaction, const Ray& ray)
{
    float a = 1.0f;
    float b = 2 * ray.direction.dot(ray.origin - p0);
    float c = (ray.origin - p0).squaredNorm() - radius * radius;
    float delta = b * b - 4 * a * c;

    if (delta < 0)
    {
        return false;
    }

    float t0 = (-b - sqrt(delta)) / 2 * a;
    float t1 = (-b + sqrt(delta)) / 2 * a;

    if (t1 < 0)
    {
        return false;
    }
    else if (t0 < 0 && t1 >= 0)
    {
        t0 = t1;
    }

    if (t0 < ray.range_min || t0 > ray.range_max)
    {
        return false;
    }

    interaction.entry_dist = t0;
    interaction.exit_dist = t1;
    interaction.entry_point = ray.getPoint(t0);
    Eigen::Vector3f r_vec = interaction.entry_point - p0;
    interaction.normal = r_vec.normalized();
    if (material != nullptr)
    {
        interaction.material = (void*)material;
    }
    interaction.type = Interaction::Type::GEOMETRY;

    return true;
}

void Sphere::buildBoundingBox()
{
    bounding_box = AABB(p0, radius);
}


/**
 * TriangleMesh class
 */

TriangleMesh::TriangleMesh(std::string file_path, BRDF* mat)
{
    setMaterial(mat);

    std::vector<Eigen::Vector2f> out_uvs;
    std::vector<int> out_vt_index;
    loadObj(file_path.c_str(), vertices, out_uvs, normals, vertices_index, out_vt_index, normals_index);
    
    num_triangles = vertices_index.size() / 3;

    has_grid = false;

    buildBoundingBox();
}

bool TriangleMesh::raySingleTriangleIntersection(Interaction& interaction, const Ray& ray, int v0_idx, int v1_idx, int v2_idx) const
{
    /**
     * TODO: Ray intersection test with single triangle
     * Note: Remember that normals are interpolated using barycentric coordinates.
     */

    UNREACHABLE;
}

bool TriangleMesh::rayIntersection(Interaction& interaction, const Ray& ray)
{
    Interaction final_interaction;
    if (has_grid) {
        /**
         * TODO: Use uniform grid to handle triangle intersection here
         * Note: Grid traversal algorithm must be used here.
         */
        
        UNREACHABLE;

    } else {
        for (int i = 0; i < num_triangles; i++) {
            Interaction cur_it;
            if (raySingleTriangleIntersection(cur_it, ray, 3 * i, 3 * i + 1, 3 * i + 2)) {
                if (final_interaction.entry_dist == -1 || cur_it.entry_dist < final_interaction.entry_dist) {
                    final_interaction = cur_it;
                }
            }
        }
    }

    if (final_interaction.entry_dist != -1)
    {
        interaction = final_interaction;
        if (material != nullptr)
        {
            interaction.material = material;
        }
        interaction.type = Interaction::Type::GEOMETRY;

        return true;
    }

    return false;
}

void TriangleMesh::buildBoundingBox()
{

    bounding_box.lb = vertices[0].cwiseMin(vertices[1]);
    bounding_box.ub = vertices[0].cwiseMax(vertices[1]);
    for (int i = 2; i < vertices.size(); i++)
    {
        bounding_box.lb = bounding_box.lb.cwiseMin(vertices[i]);
        bounding_box.ub = bounding_box.ub.cwiseMax(vertices[i]);
    }
}

void TriangleMesh::applyTransformation(const Eigen::Affine3f& t)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        vertices[i] = t * vertices[i];
    }

    Eigen::Matrix3f t_inv_tr = t.linear().inverse().transpose();
    for (int i = 0; i < normals.size(); i++)
    {
        normals[i] = (t_inv_tr * normals[i]).normalized();
    }

    buildBoundingBox();
}

void TriangleMesh::buildUniformGrid() {
    /**
     * TODO: Build uniform grid here
     * Note: you may need to build your own data structures in the accel_struct.hpp and accel_struct.cpp
     */

    UNREACHABLE;
    
    has_grid = true;
}