#include <rt/integrators/raytrace.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/dummy.h>
#include <rt/coordmappers/world.h>

namespace rt {

RayTracingIntegrator::RayTracingIntegrator(World* world): Integrator(world){}

WorldMapper RayTracingIntegrator::defaultMapper = WorldMapper();

RGBColor RayTracingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */ 
    Intersection hit = world->scene->intersect(ray);
    
    if(hit){
        Point hitPoint = hit.hitPoint();
        Vector normal = hit.normal().normalize();
        
        //texture mapping
        CoordMapper * mapper = hit.solid->texMapper;
        if(!mapper) mapper = &defaultMapper;     // default mapper
        Point texPoint = mapper->getCoords(hit);

        // We have to offset the hitPoint to avoid shadow acne
        Point offsetHitPoint = hitPoint + normal * epsilon;
        RGBColor radiance = RGBColor::rep(0.f);
        
        for(auto &l : world->light) {
            LightHit shadowRay = l->getLightHit(offsetHitPoint);
            shadowRay.direction = shadowRay.direction.normalize();
            if(dot(shadowRay.direction, normal) > epsilon) {
                Intersection obstacle = world->scene->intersect(Ray(offsetHitPoint, shadowRay.direction));
                if(!obstacle || obstacle.distance >= shadowRay.distance-epsilon*10) {
                    RGBColor reflectance = hit.solid->material->getReflectance(texPoint, normal, -ray.d, shadowRay.direction);
                    radiance = radiance + reflectance * l->getIntensity(shadowRay);
                }
            }
        } 
        radiance = radiance + hit.solid->material->getEmission(texPoint, normal, ray.d);   
        return radiance;
    }
    else return RGBColor::rep(0.f);
}

}