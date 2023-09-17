#include <rt/coordmappers/environment.h>
#include <rt/intersection.h>

namespace rt
{

	EnvironmentMapper::EnvironmentMapper(const Vector& zenith, const Vector& azimuthRef):
		zenith((zenith - azimuthRef * dot(azimuthRef, zenith)).normalize()),
		azimuthRefx(azimuthRef.normalize()),
		azimuthScale(azimuthRef.length()),
		zenithScale(zenith.length())
	{
		azimuthRefy = cross(this->zenith, this->azimuthRefx);
	}

	Point EnvironmentMapper::getCoords(const Intersection &hit) const
	{
		Vector op = hit.ray.d.normalize();
		float theta = ((acos(rt::dot(op, zenith)) / pi) - 0.5f) / zenithScale + 0.5f;

		float x = rt::dot(op, azimuthRefx);
		float y = rt::dot(op, azimuthRefy);

		return Point(
			(- atan2(y, x)) / (2 * pi * azimuthScale),
			theta,
			0
		);
	}

}