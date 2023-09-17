#ifndef CG1RAYTRACER_PRIMMOD_BMAP_HEADER
#define CG1RAYTRACER_PRIMMOD_BMAP_HEADER

#include <rt/primitive.h>
#include <rt/coordmappers/tmapper.h>
#include <core/matrix.h>

namespace rt {

class Triangle;
class Texture;

class BumpMapper : public Primitive {
    Triangle* base;
    Texture* bumpmap;
    Vector wx, wy;
    TriangleMapper b_mapper;
    float vscale;
public:
    BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3, float vscale);
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float tmin = 0.f, float tmax = FLT_MAX) const;
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
    virtual void bake(const Matrix &m);
};

}

#endif