#include <rt/cameras/environment.h>
#include <rt/ray.h>
#include <cmath>
#include <core/scalar.h>

namespace rt {

EnvironmentCamera::EnvironmentCamera(const Point& center, const Vector& forward, const Vector& up, 
                            const float fovx, const float fovy)
{
    /* TODO */
    this->center = center;
    this->forward = forward.normalize();
    this->up = up.normalize();
    this->side = cross(this->up, this->forward).normalize();
    this->up = cross(this->side, this->forward).normalize();
    this->fovx = fovx;
    this->fovy = fovy;       
}

Ray EnvironmentCamera::getPrimaryRay(float x, float y) const {
    
    float theta = fovy/2. * y;
    float phi = fovx/2. * x;
    
    Vector dir = cos(theta) * cos(phi) * this->side +
                cos(theta) * sin(phi) * this->up + 
                sin(theta) * this->forward;
    return Ray(this->center, dir.normalize());
}

}
