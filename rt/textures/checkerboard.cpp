#include <rt/textures/checkerboard.h>
#include <core/point.h>
#include <math.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black) : white(white), black(black)
{
    /* TODO */
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {
    /* TODO */ 
    if (int(floor(coord.x/0.5) + floor(coord.y/0.5) + floor(coord.z/0.5)) % 2) 
        return black;
    else
        return white;
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
    CG_UNUSED(coord);
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
    CG_UNUSED(coord);
    /* TODO */ NOT_IMPLEMENTED;
}

}