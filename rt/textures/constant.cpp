#include <rt/textures/constant.h>

namespace rt {

ConstantTexture::ConstantTexture()
{
    /* TODO */
}

ConstantTexture::ConstantTexture(const RGBColor& color) : color(color)
{
    /* TODO */
}

RGBColor ConstantTexture::getColor(const Point& coord) {
    /* TODO */ 
    return color;
}

RGBColor ConstantTexture::getColorDX(const Point& coord) {
    /* TODO */ 
    return RGBColor::rep(0.f);
}

RGBColor ConstantTexture::getColorDY(const Point& coord) {
    /* TODO */ 
    return RGBColor::rep(0.f);
}

}