#include <core/scalar.h>
#include <core/image.h>
#include <rt/renderer.h>
#include <rt/ray.h>
#include <iostream>
#include <rt/cameras/camera.h>
#include <rt/integrators/integrator.h>
#include <core/random.h>
#include <thread>

namespace rt
{

    Renderer::Renderer(Camera *cam, Integrator *integrator)
        : cam(cam), integrator(integrator), samples(1)
    {
    }

    void Renderer::render(Image &img)
    {
        /* TODO */
    
        Image num_samples(img);
        auto render_threaded = [this](Image& img, Image& num_samples, int start) {
            int w = img.width();
            int h = img.height();
            
            float x, y;

            for (int i = start; i < w; i += THREAD_COUNT)
            {
                for (int j = 0; j < h; j++)
                {
                    RGBColor pixel = RGBColor::rep(0.f);
                    RGBColor pixel2 = RGBColor::rep(0.f);
                    int s;
                    for (s = 0; s < this->samples; s++) {
                        if (this->samples == 1) {
                            x = 2.0f * (i + 0.5) / w - 1.0f;
                            y = 1.0f - 2.0f * (j + 0.5) / h;
                        }
                        else {
                            x = 2.0f * (i + random()) / w - 1.0f;
                            y = 1.0f - 2.0f * (j + random()) / h; 
                        }
                        
                        RGBColor c = integrator->getRadiance(cam->getPrimaryRay(x, y));
                        pixel = pixel + c;
                        pixel2 = pixel2 + c * c;
                        if (s > MIN_SAMPLES && (pixel2 / s - pixel * pixel / (s * s)).abs() < TOLERANCE)
                            break;
                    }

                    img(i, j) = pixel/float(s);
                    num_samples(x, y) = RGBColor::rep(s / this->samples);
                    
                }
            }
        };
        auto t1 = std::chrono::steady_clock::now();
            
        if (THREAD_COUNT > 1) {
            std::vector<std::thread*> threads;
            for (int i = 0; i < THREAD_COUNT; i++)
                threads.push_back(new std::thread(render_threaded, std::ref(img), std::ref(num_samples), i));
            for (int i = 0; i < THREAD_COUNT; i++) {
                threads[i]->join();
                delete threads[i];
            }
        }
        else {
            render_threaded(img, num_samples, 0);
        }
        auto t2 = std::chrono::steady_clock::now();

        std::chrono::duration<double, std::ratio<1,1>> ms_double = t2 - t1;
        std::cout << "Render function executed in : " << ms_double.count() << " seconds" << std::endl;
    
    }
}

rt::RGBColor a1computeColor(rt::uint x, rt::uint y, rt::uint width, rt::uint height);

namespace rt
{

    void Renderer::test_render1(Image &img)
    {
        CG_UNUSED(img);
        /*TODO*/
        for (uint i = 0; i < img.width(); i++)
        {
            for (uint j = 0; j < img.height(); j++)
            {
                img(i, j) = a1computeColor(i, j, img.width(), img.height());
            }
        }
    }
}

rt::RGBColor a2computeColor(const rt::Ray &r);

namespace rt
{

    void Renderer::test_render2(Image &img)
    {
        CG_UNUSED(img);
        /* TODO */
        float width = img.width();
        float height = img.height();
        for (uint i = 0; i < img.width(); i++)
        {
            float x = 2.0f * (i + 0.5) / width - 1.0f;

            for (uint j = 0; j < img.height(); j++)
            {
                float y = 1.0f - 2.0f * (j + 0.5) / height;
                img(i, j) = a2computeColor(cam->getPrimaryRay(x, y));
            }
        }
    }
}
