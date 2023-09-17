#ifndef CG1RAYTRACER_BBOX_HEADER
#define CG1RAYTRACER_BBOX_HEADER

#include <utility>
#include <core/point.h>
#include <core/vector.h>

namespace rt {

class Ray;

enum BoxType{empty, full, limited};
    
class BBox {
public:
    Point min, max, centroid;
    BoxType boxType;

    BBox() {}
    BBox(const Point& min, const Point& max);
    
    static BBox empty();
    static BBox full();

    void extend(const Point& point);
    void extend(const BBox& bbox);
    void clear();
    
    Vector diagonal() const; 
    float area() const;
    
    std::pair<float, float> intersect(const Ray& ray) const;

    bool isUnbound() const;
};

}

#endif