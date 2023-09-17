#ifndef CG1RAYTRACER_CAMERAS_FISHEYE_HEADER
#define CG1RAYTRACER_CAMERAS_FISHEYE_HEADER

#include <rt/cameras/camera.h>
#include <core/vector.h>
#include <core/point.h>

namespace rt {

class FisheyeCamera : public Camera {
public:
    Point center;
    Vector forward;
    Vector up;
    float fov;

    FisheyeCamera(
        const Point& center,
        const Vector& forward,
        const Vector& up,
        float fov
        );

    virtual Ray getPrimaryRay(float x, float y) const;
private:
    Vector side;
};

}


#endif


