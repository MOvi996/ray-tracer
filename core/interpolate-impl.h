#include <core/interpolate.h>

namespace rt {

template <typename T>
T lerp(const T& px0, const T& px1, float xPoint) {
    /* TODO */ 
    rt_assert(xPoint >= 0 && xPoint <=1);
    return px0 + (px1 - px0) * xPoint;
}

template <typename T>
T lerpbar(const T& a, const T& b, const T& c, float aWeight, float bWeight) {
    /* TODO */ 
    rt_assert(aWeight + bWeight <= 1);
    return a * aWeight + b * bWeight + c * (1 - aWeight - bWeight);
}

template <typename T>
T lerp2d(const T& px0y0, const T& px1y0, const T& px0y1, const T& px1y1, float xWeight, float yWeight) {
    /* TODO */ 
    return lerp(lerp(px0y0, px1y0, xWeight), lerp(px0y1, px1y1, xWeight), yWeight);
}

template <typename T>
T lerp3d(const T& px0y0z0, const T& px1y0z0, const T& px0y1z0, const T& px1y1z0,
    const T& px0y0z1, const T& px1y0z1, const T& px0y1z1, const T& px1y1z1,
    float xPoint, float yPoint, float zPoint)
{
    /* TODO */

    return lerp(lerp2d(px0y0z0, px1y0z0, px0y1z0, px1y1z0, xPoint, yPoint), 
                lerp2d(px0y0z1, px1y0z1, px0y1z1, px1y1z1, xPoint, yPoint),
                zPoint);
}

}