#include <rt/coordmappers/world.h>

namespace rt {

Point WorldMapper::getCoords(const Intersection& hit) const {
    /* TODO */ 
    Point w_coord = hit.hitPoint();
    return Point(w_coord.x * scale.x,
                 w_coord.y * scale.y,
                 w_coord.z * scale.z);
}

WorldMapper::WorldMapper() : scale(Vector::rep(1.f))
{
    /* TODO */
}

WorldMapper::WorldMapper(const Vector& scale) : scale(scale)
{
    /* TODO */
}

}