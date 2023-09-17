#include <rt/integrators/casting.h>
#include <rt/world.h>
#include <iostream>

namespace rt {

RGBColor RayCastingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */ 
    Intersection hit = world->scene->intersect(ray);
    if(hit){
        float gray = dot(-ray.d, hit.normal());
        return RGBColor::rep(gray).clamp();
    }
    return RGBColor::rep(0.);
}

}
