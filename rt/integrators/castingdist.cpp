#include <rt/integrators/castingdist.h>
#include <rt/world.h>
#include <core/scalar.h>
#include <core/assert.h>

namespace rt {

RayCastingDistIntegrator::RayCastingDistIntegrator(World* world, const RGBColor& nearColor, float nearDist, const RGBColor& farColor, float farDist)
    : Integrator(world)
{
    /* TODO */
    this->nearDist = nearDist;
    this->farDist = farDist;
    this->nearColor = nearColor;
    this->farColor = farColor;
}

RGBColor RayCastingDistIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */ 
    Intersection hit = world->scene->intersect(ray);
    if(hit){
        float gray = dot(-ray.d, hit.normal());
        gray = max(0.f, gray);
        float distFactor = (hit.distance - nearDist)/(farDist - nearDist);
        distFactor = max(min(distFactor,1.0f), 0.0f);
        return RGBColor(gray * (nearColor * (1 - distFactor) + farColor * (distFactor)));
    }
    return RGBColor::rep(0.);

}

}
