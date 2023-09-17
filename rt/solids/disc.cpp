#include <rt/solids/disc.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
    /* TODO */
    this->center = center;
    this->normal = normal.normalize();
    this->radius = radius;
    this->material = material;
}

BBox Disc::getBounds() const {
    /* TODO */ 
    Vector inv_normal = Vector(sqrt(1-sqr(normal.x)),sqrt(1-sqr(normal.y)), sqrt(1-sqr(normal.z)));
    Point b0 = center - inv_normal * radius;
    Point b1 = center + inv_normal * radius;
    return BBox(b0, b1);
}

Intersection Disc::intersect(const Ray& ray, float tmin, float tmax) const {
    /* TODO */ 
    float den = dot(ray.d, this->normal);
    if(fabsf(den) < epsilon){
        return Intersection::failure();
    }
    float t = (dot(this->center - ray.o, this->normal))/den;
    Point p = ray.getPoint(t);
    
    if(t > tmin && t < tmax && (p - this->center).length() < this->radius){
        return Intersection(t, ray, this, this->normal.normalize(), p);
    }
    return Intersection::failure();
}


Solid::Sample Disc::sample() const {
    NOT_IMPLEMENTED;
}

float Disc::getArea() const {
    /* TODO */ 
    return pi * sqr(radius);
}



}
