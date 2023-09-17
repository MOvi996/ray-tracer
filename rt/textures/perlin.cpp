#include <rt/textures/perlin.h>
#include <core/interpolate.h>
#include <core/point.h>
#include <math.h>

namespace rt {

// returns a value in range -1 to 1
static inline float noise(int x, int y, int z) {
    int n = x + y * 57 + z * 997;
    n = (n << 13) ^ n;
    return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

PerlinTexture::PerlinTexture(const RGBColor& white, const RGBColor& black) : white(white), black(black)
{
    /* TODO */
}

rt::RGBColor PerlinTexture::getColor(const Point& coord) {
    float turbulence = 0;
    float sum_amplitudes = 0;

    for (auto octave : octaves)
    {
        float amp = octave.first;
        float freq = octave.second;

        float x000 = noise(floor(freq*coord.x), floor(freq*coord.y), floor(freq*coord.z));
        float x100 = noise(ceil(freq*coord.x), floor(freq*coord.y), floor(freq*coord.z)); 
        float x010 = noise(floor(freq*coord.x), ceil(freq*coord.y), floor(freq*coord.z));
        float x110 = noise(ceil(freq*coord.x), ceil(freq*coord.y), floor(freq*coord.z));
        float x001 = noise(floor(freq*coord.x), floor(freq*coord.y), ceil(freq*coord.z));
        float x101 = noise(ceil(freq*coord.x), floor(freq*coord.y), ceil(freq*coord.z));
        float x011 = noise(floor(freq*coord.x), ceil(freq*coord.y), ceil(freq*coord.z));
        float x111 = noise(ceil(freq*coord.x), ceil(freq*coord.y), ceil(freq*coord.z));

        turbulence += amp * lerp3d(x000, x100, x010, x110, x001, x101, x011, x111, 
                            fmod(fmod(freq * coord.x, 1) + 1, 1),
                            fmod(fmod(freq * coord.y, 1) + 1, 1),
                            fmod(fmod(freq * coord.z, 1) + 1, 1));
        
        sum_amplitudes += amp;

    }
    
    // truncation 
    turbulence = (turbulence / sum_amplitudes) + 0.5f;
    turbulence = std::min(1.0f, std::max(fabs(turbulence), 0.0f));
    rt_assert(turbulence >= 0 && turbulence <= 1);
    return lerp(black, white, turbulence);
}

rt::RGBColor PerlinTexture::getColorDX(const Point& coord) {
    CG_UNUSED(coord);

    /* TODO */ NOT_IMPLEMENTED;
}

rt::RGBColor PerlinTexture::getColorDY(const Point& coord) {
    CG_UNUSED(coord);

    /* TODO */ NOT_IMPLEMENTED;
}

void PerlinTexture::addOctave(float amplitude, float frequency) {
    /* TODO */ 
    octaves.push_back(std::pair<float, float>(amplitude, frequency));
}

}