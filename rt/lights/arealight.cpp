#include <rt/lights/arealight.h>
#include <core/color.h>

namespace rt {

LightHit AreaLight::getLightHit(const Point& p) const {
    /* TODO */ 
    Solid::Sample s = this->source->sample();
    Vector p_to_source = s.point - p;
    Vector direction = p_to_source.normalize();
    return LightHit{
       direction, p_to_source.length(), s.normal 
    };
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
    /* TODO */ 
    return (this->source->material->getEmission(Point::rep(0), Vector::rep(1), Vector::rep(1)) * this->source->getArea() * rt::dot(-irr.direction, irr.normal)) / (irr.distance * irr.distance);
}

AreaLight::AreaLight(Solid* source) : source(source)
{
    /* TODO */
}

}