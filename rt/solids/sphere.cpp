#include <rt/solids/sphere.h>

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
    /* TODO */
    this->center = center;
    this->radius = radius;
    this->material = material;
}

BBox Sphere::getBounds() const {
    /* TODO */ 
    Point b0 = Point(center.x - radius, center.y - radius, center.z - radius);
    Point b1 = Point(center.x + radius, center.y + radius, center.z + radius);
    return BBox(b0, b1);
}

Intersection Sphere::intersect(const Ray& ray, float tmin, float tmax) const {
    /* TODO */ 
    float a = dot(ray.d, ray.d);
    float b = 2 * dot(ray.d, ray.o - this->center);
    float c = dot(ray.o - this->center, ray.o - this->center) - sqr(this->radius);
    float det = sqr(b) - 4 * a * c;

    if(a==0 || det < 0){
        return Intersection::failure();
    }

    float t1 = (- b + sqrt(det)) / (2 * a);
    float t2 = (- b - sqrt(det)) / (2 * a);
    float t;
    
    // check if ray's origin is inside the sphere
    if((ray.o - center).length() <= radius){
        t = max(t1, t2);
    }
    else t = min(t1, t2);
    

    if(t > tmin && t < tmax){
        Point p = ray.getPoint(t);
        return Intersection(t, ray, this, (p - center).normalize(), ray.getPoint(t));
    }
    return Intersection::failure();
}


Solid::Sample Sphere::sample() const {
	NOT_IMPLEMENTED;
}

float Sphere::getArea() const {
    /* TODO */ 
    return 4 * pi * sqr(radius);
}

}
