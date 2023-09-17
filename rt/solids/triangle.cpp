#include <rt/solids/triangle.h>
#include <core/random.h>
#include <core/interpolate.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
    /* TODO */
    this->vertices[0] = vertices[0];    //A
    this->vertices[1] = vertices[1];    //B
    this->vertices[2] = vertices[2];    //C
    
    this->sides[0] = vertices[1] - vertices[0];     //AB
    this->sides[1] = vertices[2] - vertices[1];     //BC
    this->sides[2] = vertices[2] - vertices[0];     //AC

    this->normal = cross(this->sides[0], this->sides[2]).normalize();
    this->material = material;

}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
    /* TODO */
    this->vertices[0] = v1;    //A
    this->vertices[1] = v2;    //B
    this->vertices[2] = v3;    //C
    
    this->sides[0] = vertices[1] - vertices[0];     //AB
    this->sides[1] = vertices[2] - vertices[1];     //BC
    this->sides[2] = vertices[2] - vertices[0];     //AC

    this->normal = cross(this->sides[0], this->sides[2]).normalize();

}

BBox Triangle::getBounds() const {
    /* TODO */ 
    Point b0 = min(min(vertices[0], vertices[1]), vertices[2]);
    Point b1 = max(max(vertices[0], vertices[1]), vertices[2]);
    return BBox(b0, b1);
}

Intersection Triangle::intersect(const Ray& ray, float tmin, float tmax) const {
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
    
    t = max(tmin, t);
    t = min(tmax, t);
    
    if(t > tmin && t < tmax){
        
        Point p(1-u-v, u, v);

        return Intersection(t, ray, this, normal.normalize(), p);
    }
    return Intersection::failure();
       
}

Solid::Sample Triangle::sample() const {
    /* TODO */ 
    float a = random();
    float b = random();

    return Solid::Sample {
        lerpbar(this->vertices[0], this->vertices[1], this->vertices[2], a, b),
        this->normal
        };

}

float Triangle::getArea() const {
    /* TODO */;
    return cross(sides[0], sides[1]).length()/ 2.f;

}

}