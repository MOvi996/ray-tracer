#include <rt/primmod/nmap.h>
#include <core/assert.h>
#include <rt/solids/triangle.h>
#include <rt/textures/texture.h>
#include <core/matrix.h>

namespace rt {

    NormalMapper::NormalMapper(Triangle* base, Texture* normalmap, TriangleMapper* b_mapper, float scale)
        :base(base), normalmap(normalmap), b_mapper(b_mapper), scale(scale)
    {
        Vector edge1 = base->sides[0];
        Vector edge2 = base->sides[2];

        Vector deltaUV1 = (this->b_mapper->tv1 - this->b_mapper->tv0).normalize();
        Vector deltaUV2 = (this->b_mapper->tv2 - this->b_mapper->tv0).normalize();

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        this->t = (f * (deltaUV2.y * edge1 - deltaUV1.y * edge2)).normalize();
        this->bt = (f * (-deltaUV2.x * edge1 + deltaUV1.x * edge2)).normalize();
    }

    void NormalMapper::bake(const Matrix &m)
    {
        //base->bake(m);

        Vector edge1 = base->sides[0];
        Vector edge2 = base->sides[2];

        Vector deltaUV1 = (this->b_mapper->tv1 - this->b_mapper->tv0).normalize();
        Vector deltaUV2 = (this->b_mapper->tv2 - this->b_mapper->tv0).normalize();

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        this->t = (f * (deltaUV2.y * edge1 - deltaUV1.y * edge2)).normalize();
        this->bt = (f * (-deltaUV2.x * edge1 + deltaUV1.x * edge2)).normalize();
    }

    BBox NormalMapper::getBounds() const {
        return this->base->getBounds();
    }

    // TODO: A full implementation has to make use of the coord mappers as well!
    Intersection NormalMapper::intersect(const Ray& ray, float tmin, float tmax) const {
        Intersection inter = this->base->intersect(ray, tmin, tmax);
        if (inter) {
            Point uv = this->b_mapper->getCoords(inter);
            RGBColor normal_c = this->normalmap->getColor(uv);
            Vector n = Vector(normal_c.r * 2 - 1, normal_c.g * 2 - 1, normal_c.b * 2 - 1);

            inter.normal_ = (
                Vector(
                    t.x * n.x + bt.x * n.y + inter.normal_.x * n.z,
                    t.y * n.x + bt.y * n.y + inter.normal_.y * n.z,
                    t.z * n.x + bt.z * n.y + inter.normal_.z * n.z
                )
                ).normalize();
        }
        return inter;
    }

    void NormalMapper::setMaterial(Material* m) {
        this->base->setMaterial(m);
    }

    void NormalMapper::setCoordMapper(CoordMapper* cm) {
        this->base->setCoordMapper(cm);
    }

}