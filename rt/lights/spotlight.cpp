#include <rt/lights/spotlight.h>

namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float power, const RGBColor& intensity)    
{
    rt_assert(angle > 0);
    rt_assert(exp >= 0);
    /* TODO */
    this->position = position;
    this->direction = direction.normalize();
    this->angle = angle;
    this->exp = power;
    this->intensity = intensity;
}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
    /* TODO */ 
    float cos_lobe = dot(direction, -irr.direction);
    if(acos(cos_lobe)>angle){
        return RGBColor::rep(0.f);
    }
    RGBColor irradiance = intensity * powf(cos_lobe, exp) / (irr.distance * irr.distance);
    return irradiance;

}

}
