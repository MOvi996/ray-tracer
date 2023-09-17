#include <rt/coordmappers/cylindrical.h>
#include <math.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin, const Vector& longitudinalAxis, const Vector& polarAxis) :
    origin(origin),
    longitudinalAxis(longitudinalAxis.normalize()),
    polarAxis(polarAxis),
    polarScale(polarAxis.length()),
    longitudinalScale(longitudinalAxis.length())
{
    /* TODO */
    polarAxisx = (polarAxis - dot(polarAxis, longitudinalAxis) * longitudinalAxis).normalize();
    polarAxisy = cross(polarAxisx, longitudinalAxis);
}


Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
    /* TODO */ 
    Vector op = hit.hitPoint() - origin;
    float h = dot(op, longitudinalAxis) / longitudinalScale;

    op = op.normalize();
    float x = dot(op, polarAxisx);
    float y = dot(op, polarAxisy);

    return Point((atan2(y, x) + pi) / (2 * pi * polarScale), h, 0);
}

}