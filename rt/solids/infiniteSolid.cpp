#include <rt/solids/infiniteSolid.h>
#include <rt/solids/solid.h>
#include <rt/intersection.h>
#include <core/random.h>

namespace rt
{

    InfiniteSolid::InfiniteSolid(CoordMapper *texMapper, Material *material) : Solid(texMapper, material)
    {
    }

    BBox InfiniteSolid::getBounds() const
    {
        return BBox::full();
    }

    Intersection InfiniteSolid::intersect(const Ray &ray, float tmin, float tmax) const
    {
        if (tmax < FLT_MAX)
        {
            return Intersection::failure();
        }
        return Intersection(FLT_MAX, ray, this, ray.d, ray.getPoint(FLT_MAX));
    }

    Solid::Sample InfiniteSolid::sample() const
    {
        return Solid::Sample{ Point(random() - 0.5, random()/1.5 - 0.16, random() - 0.5), Vector::rep(1.f).normalize() };
    }

    float InfiniteSolid::getArea() const
    {
        return FLT_MAX;
    }

}
