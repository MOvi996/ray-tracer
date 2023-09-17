#include <rt/cameras/fisheye.h>
#include <rt/ray.h>
#include <cmath>
#include <core/scalar.h>

namespace rt {

FisheyeCamera::FisheyeCamera(const Point& center, const Vector& forward, const Vector& up, 
                            const float fov)
{
    /* TODO */
    this->center = center;
    this->forward = forward.normalize();
    this->up = up.normalize();
    this->side = cross(this->up, this->forward).normalize();
    this->up = cross(this->side, this->forward).normalize();
    this->fov = fov;
}

Ray FisheyeCamera::getPrimaryRay(float x, float y) const {
    
    float r = sqrt(x*x+y*y);
    float phi = atan2(y,x);
    float theta = r*fov/2.;
    
    Vector dir = sin(theta) * cos(phi) * this->side +
                sin(theta) * sin(phi) * this->up + 
                cos(theta) * this->forward;
    return Ray(this->center, dir.normalize());
}

}
