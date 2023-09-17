#include <rt/intersection.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid, const Vector& normal, const Point& local)
{
    /* TODO */
    this->distance = distance;
    this->ray = ray;
    this->solid = solid;
    this->normal_ = normal;
    this->local_ = local;
}

Intersection::operator bool() const {
    /* TODO */ 
    return this->solid != nullptr;
}

Intersection Intersection::failure() {
    /* TODO */ 
    Intersection temp = Intersection();
    temp.solid = nullptr;
    return temp;
}

Point Intersection::hitPoint() const {
    /* TODO */ 
    return ray.getPoint(distance);
}

Vector Intersection::normal() const {
    /* TODO */ 
    return normal_;
}

Point Intersection::local() const {
    /* TODO */ 
    return local_;
}

}
