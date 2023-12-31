#ifndef CG1RAYTRACER_SOLIDS_INFINITESOLID_HEADER
#define CG1RAYTRACER_SOLIDS_INFINITESOLID_HEADER

#include <rt/solids/solid.h>

namespace rt
{

    class InfiniteSolid : public Solid
    {
    public:
        InfiniteSolid() {}
        InfiniteSolid(CoordMapper *texMapper, Material *material);
        // InfinitePlane(const Point &origin, const Vector &normal, CoordMapper *texMapper, Material *material);
        virtual BBox getBounds() const;
        virtual Intersection intersect(const Ray &ray, float tmin = 0, float tmax = FLT_MAX) const;
        virtual Sample sample() const;
        virtual float getArea() const;
    };

}

#endif