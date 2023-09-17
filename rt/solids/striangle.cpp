#include <rt/solids/striangle.h>
#include <rt/intersection.h>
#include <rt/solids/triangle.h>
#include <core/interpolate.h>

namespace rt {

SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material)
: Triangle(vertices, texMapper, material)
{
    /* TODO */
    this->normals[0] = normals[0];
    this->normals[1] = normals[1];
    this->normals[2] = normals[2];
}

SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, const Vector& n1, const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material)
: Triangle(v1, v2, v3, texMapper, material)
{
    /* TODO */
    this->normals[0] = n1;
    this->normals[1] = n2;
    this->normals[2] = n3;
}

Intersection SmoothTriangle::intersect(const Ray& ray, float tmin, float tmax) const {
    /* TODO */ 
    Vector AB = sides[0];
    Vector AC = sides[2];
    float t, u, v;

    Vector cross_D_AC = cross(ray.d, AC);
    float det = dot(AB, cross_D_AC);

    if(fabsf(det) < epsilon){
        return Intersection::failure();         //ray parallel to triangle
    }
    
    float inv_det = 1.f / det;
    Vector o_v0 = ray.o - vertices[0];

    u = dot(o_v0, cross_D_AC) * inv_det;

    if(u<0 || u > 1){
        return Intersection::failure();         //pt lies outside triangle
    }

    Vector cross_ov0_AB = cross(o_v0, AB);
    v = dot(ray.d, cross_ov0_AB) * inv_det;

    if(v < 0 || u+v>1){
        return Intersection::failure();         //pt lies outside triangle
    }

    t = dot(AC, cross_ov0_AB)*inv_det;
    
    if(t > tmin && t < tmax){
            float w2 = rt::dot(rt::cross(vertices[1] - ray.o, vertices[0] - ray.o), t * ray.d);
            float w0 = rt::dot(rt::cross(vertices[2] - ray.o, vertices[1] - ray.o), t * ray.d);
            float w1 = rt::dot(rt::cross(vertices[0] - ray.o, vertices[2] - ray.o), t * ray.d);

            w0 /= (w0 + w1 + w2);
            w1 /= (w0 + w1 + w2);
            w2 /= (w0 + w1 + w2);

            Vector interpNormal = (w0 * normals[0] + w1 * normals[1] + w2 * normals[2]).normalize();
            return Intersection(t, ray, this, dot(ray.d, normal) < 0.f ? interpNormal : -interpNormal, Point(u, v, 1-u-v));
    }
        
    return Intersection::failure();
}

}