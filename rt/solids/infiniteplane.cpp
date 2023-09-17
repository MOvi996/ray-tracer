#include <rt/solids/infiniteplane.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
    /* TODO */
    this->origin = origin;
    this->normal = normal;
    //this->material = material;
}

BBox InfinitePlane::getBounds() const {
    /* TODO */ 
    return BBox::full();
}

Intersection InfinitePlane::intersect(const Ray& ray, float tmin, float tmax) const {
    /* TODO */ 
    float den = dot(ray.d, this->normal);
    if(fabsf(den) < epsilon){
        return Intersection::failure();
    }
    float t = (dot(this->origin - ray.o, this->normal))/den;
    t = max(tmin, t);
    t = min(t, tmax);

    if(t > tmin && t < tmax){
        return Intersection(t, ray, this, this->normal.normalize(), ray.getPoint(t));
    }
    return Intersection::failure();

}

Solid::Sample InfinitePlane::sample() const {
    /* TODO */ NOT_IMPLEMENTED;
}

float InfinitePlane::getArea() const {
    /* TODO */ 
    return FLT_MAX;

}

}
