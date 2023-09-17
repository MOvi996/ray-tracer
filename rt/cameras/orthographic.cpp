#include <rt/cameras/orthographic.h>
#include <core/vector.h>
#include <core/vector.h>
#include <rt/ray.h>

namespace rt {

OrthographicCamera::OrthographicCamera(const Point& center, const Vector& forward, const Vector& up, float scaleX, float scaleY)
{
    /* TODO */
    this->center = center;
    this->forward = forward;
    this->up = up;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    
    this->z = forward.normalize();
    this->y = up.normalize();
    this->x = cross(this->z, this->y).normalize();
    this->y = cross(this->x, this->z).normalize();
}

Ray OrthographicCamera::getPrimaryRay(float x, float y) const {
    /* TODO */ 
    Vector u = scaleX * x / 2.0f * this->x;
    Vector v = scaleY * y / 2.0f * this->y; 
    
    return Ray(center + u + v, this->z);
}
}
