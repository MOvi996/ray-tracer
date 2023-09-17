#include <rt/materials/combine.h>
#include <core/random.h>
namespace rt {

CombineMaterial::CombineMaterial() : sampled_mats(0)
{
    /* TODO */
}

void CombineMaterial::add(Material* m, float w) {
    /* TODO */ 
    if (m->useSampling() != SAMPLING_NOT_NEEDED)
        sampled_mats += w;
    materials.push_back(std::pair<Material*, float>(m, w));
}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir, const Vector& inDir) const {
    /* TODO */ 
    RGBColor c = RGBColor::rep(0.f);
    for (auto mat : materials) {
        if(mat.first->useSampling() != SAMPLING_ALL)
            c = c + mat.second * mat.first->getReflectance(texPoint, normal, outDir, inDir);
    };
    return c;
}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ 
    RGBColor c = RGBColor::rep(0.f);
    for (auto mat : materials) {
        c = c + mat.second * mat.first->getEmission(texPoint, normal, outDir);
    }
    return c;
}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
    /* TODO */ 
    Material::SampleReflectance s_r;
    float c = random();
    float counter = 0.f;
    for (auto mat : materials) {
        if (mat.first->useSampling() == SAMPLING_ALL || mat.first->useSampling() == SAMPLING_SECONDARY) {
            counter += mat.second / sampled_mats;
            if (c < counter) {
                Material::SampleReflectance s_r = mat.first->getSampleReflectance(texPoint, normal, outDir);
                s_r.reflectance = s_r.reflectance * mat.second;
            }
        }
    }
    return s_r;
}

Material::Sampling CombineMaterial::useSampling() const {
    /* TODO */ 
    return SAMPLING_SECONDARY;
}

}