#include <rt/integrators/recraytrace.h>
#include <rt/intersection.h>
#include <rt/world.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <rt/materials/dummy.h>

namespace rt {

WorldMapper RecursiveRayTracingIntegrator::defaultMapper = WorldMapper();

RGBColor RecursiveRayTracingIntegrator::getRadiance(const Ray& ray) const {
    /* TODO */ 
    return RecursiveRayTracingIntegrator::getRadianceRec(ray,1);
}

RGBColor RecursiveRayTracingIntegrator::getRadianceRec(const Ray& ray, int depth) const{
    if(depth >=MAX_DEPTH) return RGBColor::rep(0.f);

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

        if(hit.solid->material->useSampling() != Material::SAMPLING_ALL){
            //iteration over all lights needed.

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
        }

        if(hit.solid->material->useSampling() != Material::SAMPLING_NOT_NEEDED){
            Material::SampleReflectance sr = hit.solid->material->getSampleReflectance(
                    texPoint,
                    normal,
                    -ray.d
                );
            if (rt::dot(sr.direction, hit.normal()) < 0){
                offsetHitPoint = hitPoint - hit.normal() * epsilon * 10;
            }
            radiance = radiance + sr.reflectance * this->getRadianceRec(Ray(offsetHitPoint, sr.direction), depth + 1);        
        }

        radiance = radiance + hit.solid->material->getEmission(texPoint, normal, -ray.d);
            
        return radiance;

    }
    else
        return RGBColor::rep(0.f); 
    
}



}