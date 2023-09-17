#include <core/color.h>
#include <core/scalar.h>
#include <core/homogeneouscoord.h>

namespace rt {

RGBColor::RGBColor(const HomogeneousCoord& coord)
{
/* TODO */ NOT_IMPLEMENTED;
}

RGBColor RGBColor::operator + (const RGBColor& c) const {
    /* TODO */ 
    return RGBColor(r+c.r, g+c.g, b+c.b);
}

RGBColor RGBColor::operator - (const RGBColor& c) const {
    /* TODO */ 
    return RGBColor(r-c.r, g-c.g, b-c.b);
}

RGBColor RGBColor::operator * (const RGBColor& c) const {
    /* TODO */ 
    return RGBColor(r*c.r, g*c.g, b*c.b);
}

bool RGBColor::operator == (const RGBColor& c) const {
    /* TODO */ 
    return r==c.r && g==c.g && b==c.b;
}

bool RGBColor::operator != (const RGBColor& b) const {
    /* TODO */ 
    return this->r!=b.r || this->g != b.g || this->b != b.b; 
}

bool RGBColor::operator < (const RGBColor& c) const {
    return (r < c.r) && (b < c.b) && (g < c.g);
}


RGBColor RGBColor::clamp() const {
    /* TODO */ 
    float new_r = std::min(std::max(0.0f,r),1.0f);
    float new_g = std::min(std::max(0.0f,g),1.0f);
    float new_b = std::min(std::max(0.0f,b),1.0f);

    return RGBColor(new_r, new_g, new_b);
    
}

RGBColor RGBColor::gamma(float gam) const {
    /* TODO */ NOT_IMPLEMENTED;
}

float RGBColor::luminance() const {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor operator * (float scalar, const RGBColor& c) {
    /* TODO */ 
    return RGBColor(c.r*scalar, c.g*scalar, c.b*scalar);
}

RGBColor operator * (const RGBColor& c, float scalar) {
    /* TODO */ 
    return RGBColor(c.r*scalar, c.g*scalar, c.b*scalar);
}

RGBColor operator / (const RGBColor& c, float scalar) {
    /* TODO */ 
    return RGBColor(c.r/scalar, c.g/scalar, c.b/scalar);
}

}
