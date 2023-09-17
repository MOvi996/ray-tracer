#include <rt/lights/directional.h>
#include <core/scalar.h>
#include <core/vector.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color) : direction(direction.normalize()), intensity(color)
{
    /* TODO */
}

LightHit DirectionalLight::getLightHit(const Point& p) const {
    /* TODO */ 
    return LightHit{-direction, FLT_MAX, direction};
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
    /* TODO */ 
    return intensity;
}

}
