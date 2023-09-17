#ifndef CG1RAYTRACER_PRIMMOD_NMAP_HEADER
#define CG1RAYTRACER_PRIMMOD_NMAP_HEADER

#include <rt/primitive.h>
#include <rt/solids/solid.h>
#include <rt/solids/triangle.h>
#include <core/matrix.h>
#include <rt/textures/texture.h>
#include <rt/coordmappers/tmapper.h>

namespace rt {

    class NormalMapper : public Primitive {
        Triangle* base;
        Texture* normalmap;
        TriangleMapper* b_mapper;
        Vector t, bt;
        float scale;
    public:
        NormalMapper(Triangle* base, Texture* bumpmap, TriangleMapper* b_mapper, float scale);
        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray& ray, float tmin = 0.f, float tmax = FLT_MAX) const;
        virtual void setMaterial(Material* m);
        virtual void setCoordMapper(CoordMapper* cm);
        virtual void bake(const Matrix &m);
    };

}

#endif