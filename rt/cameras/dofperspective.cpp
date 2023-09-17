#include <rt/cameras/dofperspective.h>
#include <rt/ray.h>
#include <core/random.h>
#include <math.h>
#include <core/scalar.h>

namespace rt {

DOFPerspectiveCamera::DOFPerspectiveCamera(const Point& center, const Vector& forward, const Vector& up, float verticalOpeningAngle, float horizontalOpeningAngle, float focalDistance, float apertureRadius)
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
    this->focalDistance = focalDistance;
    this->apertureRadius = apertureRadius;
}

Ray DOFPerspectiveCamera::getPrimaryRay(float x, float y) const {
    /* TODO */ 
    Vector dir = this->z + 
                x * this->x * tan(horizontalOpeningAngle/2.) +
                y * this->y * tan(verticalOpeningAngle/2.);
    Ray ray = Ray(this->center, dir.normalize());

    if(apertureRadius > 0 && apertureRadius <=1){
        float sx = apertureRadius * sqrtf(random()) * cosf(4 * pi * pi * random());
        float sy = apertureRadius * sqrtf(random()) * sinf(4 * pi * pi * random());

        Point new_o = center + sx * this->x + sy * this->y;

        float f = focalDistance / this->z.length();
        Point focal_p = ray.getPoint(f);
        ray.o = new_o;
        ray.d = (focal_p - new_o).normalize();
        }    
    return ray;
}

}