#ifndef CG1RAYTRACER_RENDERER_HEADER
#define CG1RAYTRACER_RENDERER_HEADER

#include <core/scalar.h>
#include <rt/cameras/camera.h>
#include <core/color.h>

namespace rt {

class Image;
//class Camera;
class Integrator;

class Renderer {
public:
    Renderer(Camera* cam, Integrator* integrator);
    void setSamples(uint samples) { this->samples = samples; }
    void render(Image& img);
    void test_render1(Image& img);
    void test_render2(Image& img);
    
private:
    Camera* cam;
    Integrator* integrator;
    int samples;
    int MIN_SAMPLES = 200;
    int THREAD_COUNT = 2;
    RGBColor TOLERANCE = RGBColor::rep(0.0025f);
    
};

}

#endif