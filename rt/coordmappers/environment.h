#ifndef CG1RAYTRACER_COORDMAPPERS_ENVIRONMENT_HEADER
#define CG1RAYTRACER_COORDMAPPERS_ENVIRONMENT_HEADER

#include <rt/coordmappers/coordmapper.h>
#include <core/vector.h>

namespace rt
{

    class HomogeneousCoord;

    class EnvironmentMapper : public CoordMapper
    {
        Vector zenith;
        Vector azimuthRefx;
        Vector azimuthRefy;
        float azimuthScale;
        float zenithScale;
    public:
        EnvironmentMapper(const Vector& zenith, const Vector& azimuthRef);
        virtual Point getCoords(const Intersection& hit) const;
    };

}

#endif