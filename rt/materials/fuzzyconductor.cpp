#include <rt/materials/fuzzyconductor.h>
#include <core/scalar.h>
#include <math.h>
#include <core/random.h>

namespace rt {

FuzzyConductorMaterial::FuzzyConductorMaterial(float eta, float kappa, float fuzzyangle) : 
eta(eta), kappa(kappa), fuzzyangle(fuzzyangle)
{
    /* TODO */
}

RGBColor FuzzyConductorMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);
    CG_UNUSED(inDir);
    UNREACHABLE;
}

RGBColor FuzzyConductorMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ 
    return RGBColor::rep(0.f);
}

Material::SampleReflectance FuzzyConductorMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    
    /* TODO */ 
    rt_assert(abs(outDir.length() - 1) < epsilon);
    rt_assert(abs(normal.length() - 1) < epsilon);

    Vector inDir = - outDir + 2.f * dot(outDir, normal) * normal;
    inDir = inDir.normalize();

    float u = 2 * pi * random();
    float v = tan(fuzzyangle) * sqrtf(random());

    float x = v * cosf(2 * pi * u);
    float y = v * sinf(2 * pi * u);

    Vector vx, vy;
    if (fabsf(inDir.x) < fabsf(inDir.y) && fabsf(inDir.x) < fabsf(inDir.z))
        vx = Vector(0, -inDir.z, inDir.y).normalize();
    else if (fabsf(inDir.y) < fabsf(inDir.z))
        vx = Vector(-inDir.z, 0, inDir.x).normalize();
    else
        vx = Vector(-inDir.y, inDir.x, 0).normalize();

    vy = rt::cross(inDir, vx).normalize();

    inDir = (inDir + x * vx + y * vy).normalize();

    float cosThetaI = rt::dot(inDir, normal);

    if (cosThetaI <= 0) {
        return Material::SampleReflectance(
            inDir,
            RGBColor::rep(0)
        );
    }
    float r1 =
        ((eta * eta + kappa * kappa) * cosThetaI * cosThetaI - 2 * eta * cosThetaI + 1) /
        ((eta * eta + kappa * kappa) * cosThetaI * cosThetaI + 2 * eta * cosThetaI + 1);
    float r2 =
        ((eta * eta + kappa * kappa) - 2 * eta * cosThetaI + cosThetaI * cosThetaI) /
        ((eta * eta + kappa * kappa) + 2 * eta * cosThetaI + cosThetaI * cosThetaI);

    return Material::SampleReflectance(
        inDir,
        RGBColor::rep((r1 + r2) / 2.f)
    );
}

Material::Sampling FuzzyConductorMaterial::useSampling() const {
    /* TODO */ 
    return SAMPLING_ALL;
}

}
