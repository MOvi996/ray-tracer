#include <rt/materials/phong.h>
#include <rt/textures/texture.h>
#include<core/scalar.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent) : specular(specular), exponent(exponent)
{
    /* TODO */
}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */ 
    RGBColor color = specular->getColor(texPoint);
    Vector r_i = (- inDir + 2 * dot(inDir, normal) * normal).normalize();
    float c_s = 2*pi/(exponent+2);
    float weight = std::min(powf(std::max(0.f, dot(r_i, outDir)), exponent),1.f) * dot(inDir, normal) / c_s;
    return color * weight;
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ 
    return RGBColor::rep(0.f);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    CG_UNUSED(texPoint);
    CG_UNUSED(normal);
    CG_UNUSED(outDir);

	UNREACHABLE;
}

Material::Sampling PhongMaterial::useSampling() const {
	/* TODO */ return Material::SAMPLING_NOT_NEEDED;
}

}