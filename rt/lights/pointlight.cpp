#include <rt/lights/pointlight.h>

#include <core/vector.h>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity):
    position(position), intensity(intensity)
{

}

LightHit PointLight::getLightHit(const Point& p) const {
    Vector p_to_source = position - p;
    Vector direction = p_to_source.normalize();
    return LightHit{direction, 
                    p_to_source.length(),   //distance
                    -direction              //normal
                };
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
    return intensity / (irr.distance * irr.distance);
}

}
