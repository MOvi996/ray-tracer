#include <rt/coordmappers/tmapper.h>
#include <core/interpolate.h>

namespace rt {

TriangleMapper::TriangleMapper(Point ntv[3]) : tv0(ntv[0]), tv1(ntv[1]), tv2(ntv[2])
{
    /* TODO */
}

TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1, const Point& tv2) :
    tv0(tv0), tv1(tv1), tv2(tv2)
{
    /* TODO */
}

Point TriangleMapper::getCoords(const Intersection& hit) const {
    /* TODO */ 
    Point w_coord = hit.local();
    rt_assert(abs((w_coord.x + w_coord.y + w_coord.z) - 1) < epsilon);

    return lerpbar(tv0, tv1, tv2, w_coord.x, w_coord.y);
}

}