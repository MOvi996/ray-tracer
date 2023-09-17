#include <rt/materials/dielectric.h>
#include <math.h>
#include <core/scalar.h>

namespace rt {

DielectricMaterial::DielectricMaterial(float eta) : eta(eta)
{
    /* TODO */
}

RGBColor DielectricMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
    CG_UNUSED(inDir);
    UNREACHABLE;
}

RGBColor DielectricMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ 
    return RGBColor::rep(0.f);
}

Material::SampleReflectance DielectricMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ 
    rt_assert(abs(outDir.length() - 1) < epsilon);
    rt_assert(abs(normal.length() - 1) < epsilon);

    Vector normal_ = normal;

    float eta_i = 1;                //assuming air
    float eta_t = this->eta;
    
    if (rt::dot(normal, outDir) < 0.f) {
        normal_ = -normal_;
        eta_i = this->eta;
        eta_t = 1.f;
    }

    float eta_r = eta_i / eta_t;

    float cosThetaI = dot(normal_, outDir);

    Vector T = (eta_r* cosThetaI - sqrtf(1 - eta_r* eta_r* (1.f - cosThetaI * cosThetaI))) * normal_ - eta_r* outDir;

    float sin2_ThetaI = 1 - cosThetaI * cosThetaI;
    float sin2_ThetaT = sin2_ThetaI * eta_r* eta_r;
    float cosThetaT = sqrtf(1.0f - sin2_ThetaT);

    float r1 =((eta_t * cosThetaI) - (eta_i * cosThetaT)) /
                ((eta_t * cosThetaI) + (eta_i * cosThetaT));

    float r2 = ((eta_i * cosThetaI) - (eta_t * cosThetaT)) / 
                ((eta_i * cosThetaI) + (eta_t * cosThetaT));
        
    float Fr = (r1 * r1 + r2 * r2) / 2.f; 
    
    if (eta_i > eta_t) {
        // check for total internal reflection
        if (sqrtf(sin2_ThetaI) > eta_t / eta_i)
        { 
            return Material::SampleReflectance(
                (-outDir + 2 * rt::dot(outDir, normal_) * normal_).normalize(),
                RGBColor::rep(1.f));
        }
        else 
        {
            return Material::SampleReflectance(
                T.normalize(),
                RGBColor::rep(1 - Fr));
        }    
    
    }

    if (random() < 0.5) {
        return Material::SampleReflectance(
            (-outDir + 2 * rt::dot(outDir, normal_) * normal_).normalize(),
            RGBColor::rep(2* Fr));
    }
    else {
        return Material::SampleReflectance(
            T.normalize(),
            RGBColor::rep(1 - Fr)*2);
    }
    
}

Material::Sampling DielectricMaterial::useSampling() const {
    /* TODO */ 
    return SAMPLING_ALL;
}

}