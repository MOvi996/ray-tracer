#include <rt/materials/conductor.h>
#include <core/scalar.h>


namespace rt {

ConductorMaterial::ConductorMaterial(float eta, float kappa) : eta(eta), kappa(kappa)
{
    /* TODO */
}

RGBColor ConductorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
    CG_UNUSED(inDir);
    UNREACHABLE;
}

RGBColor ConductorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    
    /* TODO */ 
    return RGBColor::rep(0.f);
}

Material::SampleReflectance ConductorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {    
    /* TODO */ 
    //just in case
    rt_assert(abs(outDir.length() - 1) < epsilon);
    rt_assert(abs(normal.length() - 1) < epsilon);

    Vector inDir = - outDir + 2.f * dot(outDir, normal) * normal;
    inDir = inDir.normalize();

    float cosThetaI = dot(inDir, normal);

    if(cosThetaI <=0) {
        return Material::SampleReflectance();
    }

    float r1 = ((eta * eta + kappa * kappa) * cosThetaI * cosThetaI - 2 * eta * cosThetaI + 1.f) / 
               ((eta * eta + kappa * kappa) * cosThetaI * cosThetaI + 2 * eta * cosThetaI + 1.f);

    float r2 = ((eta * eta + kappa * kappa) - 2 * eta * cosThetaI + cosThetaI * cosThetaI) / 
               ((eta * eta + kappa * kappa) + 2 * eta * cosThetaI + cosThetaI * cosThetaI);

    float r = (r1 + r2) / 2.f;

    return Material::SampleReflectance(
        inDir,
        RGBColor::rep(r)
    );
     
}

Material::Sampling ConductorMaterial::useSampling() const {
    /* TODO */ 
    return SAMPLING_ALL;
}

}