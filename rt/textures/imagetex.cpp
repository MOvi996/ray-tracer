#include <rt/textures/imagetex.h>
#include <math.h>
#include <core/interpolate.h>
#include <core/point.h>


namespace rt {

ImageTexture::ImageTexture()
{
    /* TODO */
}

ImageTexture::ImageTexture(const std::string& filename, BorderHandlingType bh, InterpolationType i) : bh(bh), i(i)
{
    /* TODO */
    image.readPNG(filename);
}

ImageTexture::ImageTexture(const Image& image, BorderHandlingType bh, InterpolationType i) : 
    image(image), bh(bh), i(i)
{
    /* TODO */
}

RGBColor ImageTexture::getColor(const Point& coord) {
    /* TODO */ 
    Point norm_coord;       //t (t_u, t_v, t_w)
    if(bh == CLAMP){
        norm_coord = min(max(coord, Point::rep(0.f)), Point::rep(1.f));
    }
    
    else        
    {
        norm_coord = Point(absfractional(coord.x),absfractional(coord.y), absfractional(coord.z));
        
        if(bh == MIRROR){
            if (int(floor(coord.x)) % 2 == 1)
                    norm_coord.x = absfractional(1 - absfractional(coord.x));
            if (int(floor(coord.y)) % 2 == 1)
                    norm_coord.y = absfractional(1 - absfractional(coord.y));
            if (int(floor(coord.z)) % 2 == 1)
                    norm_coord.z = absfractional(1 - absfractional(coord.z));
        }
    }

    if (i == NEAREST){
        float u = norm_coord.x * image.width() + 0.5;           // t_u * resU
        float v = norm_coord.y * image.height() + 0.5;          // t_v * resV
        
        //return image(std::min(uint(floor(u)), image.width() - 1), std::min(uint(floor(v)), image.height() - 1));
        return image(floor(u) - 1, floor(v) - 1);
    }
    else if(i == BILINEAR)        //BILINEAR
    { 
        float x = norm_coord.x * image.width() + 0.5;           // t_u * resU
        float y = norm_coord.y * image.height() + 0.5;          // t_v * resV
        int floorx = x > 1 ? floorf(x) - 1 : image.width() - 1;
        int floory = y > 1 ? floorf(y) - 1 : image.height() - 1;
        int ceilx = x < image.width() - 1 ? ceilf(x) - 1 : 0;
        int ceily = y < image.height() - 1 ? ceilf(y) - 1 : 0;
        return lerp2d(
            image(floorx, floory),
            image(ceilx, floory),
            image(floorx, ceily),
            image(ceilx, ceily),
            absfractional(x),
            absfractional(y)
        ) ;
        // float u = norm_coord.x * (image.width() - 1);           // t_u * (resU - 1)
        // float v = norm_coord.y * (image.height() - 1);          // t_v * (resV - 1)

        // float f_u = absfractional(u);                                 
        // float f_v = absfractional(v);
        
        // return lerp2d(image(int(floorf(u)),int(floorf(v))),
        //               image(int(floorf(u)),int(floorf(v)) + 1),
        //               image(int(floorf(u))+1,int(floorf(v))),
        //               image(int(floorf(u))+1,int(floorf(v))+1),
        //               f_u,
        //               f_v);

    }
    else return RGBColor();

}

RGBColor ImageTexture::getColorDX(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

RGBColor ImageTexture::getColorDY(const Point& coord) {
    /* TODO */ NOT_IMPLEMENTED;
}

}