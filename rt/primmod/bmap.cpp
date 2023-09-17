#include <rt/primmod/bmap.h>
#include <core/assert.h>
#include <rt/solids/triangle.h>
#include <rt/textures/texture.h>
#include <core/matrix.h>

namespace rt {

BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale):
    base(base), bumpmap(bumpmap), b_mapper(TriangleMapper(bv1, bv2, bv3)), vscale(vscale)
{
    Vector edge1 = base->sides[0];
    Vector edge2 = base->sides[2];

    Vector deltaUV1 = (b_mapper.tv1 - b_mapper.tv0).normalize();
    Vector deltaUV2 = (b_mapper.tv2 - b_mapper.tv0).normalize();
    //base2 = (base2 - base2 * rt::dot(base2, base1)).normalize();
    //assert(fabsf(rt::dot(base1, base2)) < epsilon);
    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    Vector tangent = (f * (deltaUV2.y * edge1 - deltaUV1.y * edge2)).normalize();
    Vector bitangent = (f * (-deltaUV2.x * edge1 + deltaUV1.x * edge2)).normalize();

    //Matrix m = Matrix::system(tangent, bitangent, base->normal);

    wx = -tangent;
    wy = -bitangent;

}

void BumpMapper::bake(const Matrix &m)
{
    //this->base->bake(m);

    Vector edge1 = base->sides[0];
    Vector edge2 = base->sides[2];

    Vector deltaUV1 = (b_mapper.tv1 - b_mapper.tv0).normalize();
    Vector deltaUV2 = (b_mapper.tv2 - b_mapper.tv0).normalize();
    //base2 = (base2 - base2 * rt::dot(base2, base1)).normalize();
    //assert(fabsf(rt::dot(base1, base2)) < epsilon);
    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    Vector tangent = (f * (deltaUV2.y * edge1 - deltaUV1.y * edge2)).normalize();
    Vector bitangent = (f * (-deltaUV2.x * edge1 + deltaUV1.x * edge2)).normalize();

    wx = -tangent;
    wy = -bitangent;
}

BBox BumpMapper::getBounds() const {
    return this->base->getBounds();
}

// TODO: A full implementation has to make use of the coord mappers as well!
Intersection BumpMapper::intersect(const Ray& ray, float tmin, float tmax) const {
    Intersection inter = this->base->intersect(ray, tmin, tmax);
    if (inter) {
        Point uv = this->b_mapper.getCoords(inter);
        RGBColor dx = this->bumpmap->getColorDX(uv);
        RGBColor dy = this->bumpmap->getColorDY(uv);
        //std::cout << dx.r << " " << dy.r << std::endl;
        inter.normal_ = (inter.normal_ + dx.r * vscale * wx / 6.28 + dy.r * vscale * wy / 6.28).normalize();
    }
    return inter;
}

void BumpMapper::setMaterial(Material* m) {
    this->base->setMaterial(m);
}

void BumpMapper::setCoordMapper(CoordMapper* cm) {
    this->base->setCoordMapper(cm);
}

}