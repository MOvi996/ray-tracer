#include <rt/cameras/perspective.h>
#include <rt/ray.h>
#include <cmath>

namespace rt {

PerspectiveCamera::PerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle)
{
    /* TODO */
    this->center = center;
    this->forward = forward;
    this->up = up;
    this->z = forward.normalize();
    this->y = up.normalize();
    this->x = cross(z, y).normalize();
    this->y = cross(x, z).normalize();
    this->verticalOpeningAngle = verticalOpeningAngle;
    this->horizontalOpeningAngle = horizontalOpeningAngle;       
}

Ray PerspectiveCamera::getPrimaryRay(float x, float y) const {
    /* TODO */ 
    Vector dir = this->z + 
                x * this->x * tan(horizontalOpeningAngle/2.) +
                y * this->y * tan(verticalOpeningAngle/2.);
    return Ray(this->center, dir.normalize());
}

}
