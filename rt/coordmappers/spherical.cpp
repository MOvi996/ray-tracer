#include <rt/coordmappers/spherical.h>

namespace rt {

SphericalCoordMapper::SphericalCoordMapper(const Point& origin, const Vector& zenith, const Vector& azimuthRef): 
    origin(origin),
    zenith(zenith.normalize()),
    azimuthRef(azimuthRef),
    azimuthScale(azimuthRef.length()),
    zenithScale(zenith.length())
{
    /* TODO */
    azimuthRefx = (azimuthRef - zenith * dot(azimuthRef, zenith)).normalize();
    azimuthRefy = cross(azimuthRefx, zenith);
}

Point SphericalCoordMapper::getCoords(const Intersection& hit) const {
    /* TODO */
    Vector op = (hit.hitPoint() - origin).normalize();
    float theta = acos(dot(op, zenith)) / (pi * zenithScale);

    float x = dot(op, azimuthRefx);
    float y = dot(op, azimuthRefy);

    return Point((atan2(y, x) + pi) / (2 * pi * azimuthScale), theta, 0);
}

}