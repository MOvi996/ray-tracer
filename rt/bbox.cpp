#include <rt/bbox.h>
#include <core/scalar.h>
#include <rt/ray.h>

namespace rt {

BBox::BBox(const Point& min, const Point& max){
        /* TODO */
        this->min = min;
        this->max = max;
        this->centroid = Point((min.x+max.x)/2.f, (min.y+max.y)/2.f, (min.z+max.z)/2.f);
        this->boxType = BoxType::limited; 
        rt_assert(min <= max);
            
}

Vector BBox::diagonal() const{
    /* TODO */ 
    return max - min;
}

float BBox::area() const {
    /* TODO */ 
    if(boxType == BoxType::empty){
        return 0;
    }
    else if (boxType == BoxType::full){
        return FLT_MAX;
    }
    Vector diag = this->diagonal();
    return 2 * (diag.x * diag.y + diag.y * diag.z + diag.z * diag.x);
}

// Point BBox::getCentroid() const {
//     return Point((min.x+max.x)/2.f, (min.y+max.y)/2.f, (min.z+max.z)/2.f);
// }

BBox BBox::empty() {
    /* TODO */ 
    BBox temp = BBox();
    temp.boxType = BoxType::empty;
    return temp;
}

BBox BBox::full() {
    /* TODO */ 
    BBox temp = BBox(
        Point(-FLT_MAX, -FLT_MAX,-FLT_MAX), 
        Point(FLT_MAX, FLT_MAX, FLT_MAX));
    temp.boxType = BoxType::full;
    return temp;
}


void BBox::extend(const Point& point) {
    /* TODO */ 
    if (boxType == BoxType::empty){
        this->min = point;
        this->max = point;
        this->boxType = BoxType::limited;
    
    }
    else
    {
        this->min = rt::min(min, point);
        this->max = rt::max(max, point);    
    }
    this->centroid = Point((min.x+max.x)/2.f, (min.y+max.y)/2.f, (min.z+max.z)/2.f);
     
}

void BBox::extend(const BBox& bbox) {
    /* TODO */ 
    if (bbox.boxType == BoxType::full){
        this->min = Point(-FLT_MAX, -FLT_MAX,-FLT_MAX), 
        this->max = Point(FLT_MAX, FLT_MAX, FLT_MAX);
        this->boxType = BoxType::full;
    }
    else if(bbox.boxType == BoxType::empty || this->boxType == BoxType::full){
        return;
    }
    else if(this->boxType == BoxType::empty){
        this->min = bbox.min;
        this->max = bbox.max;
        this->boxType = BoxType::limited;
    
    }
    else{
        this->min = rt::min(bbox.min, this->min);
        this->max = rt::max(bbox.max, this->max);
    }
    this->centroid = Point((min.x+max.x)/2.f, (min.y+max.y)/2.f, (min.z+max.z)/2.f);
}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
    /* TODO */ 
    if(boxType == BoxType::empty) {
        return std::pair<float, float>(FLT_MAX, FLT_MAX);
    }
    else if (boxType == BoxType::full){
        return std::pair<float, float>(0, FLT_MAX);
    }

    //rt_assert(ray.d.x!=0 && ray.d.y!=0 && ray.d.z!=0);
    Vector r_inv_d = Vector(1.f / ray.d.x, 1.f / ray.d.y, 1.f / ray.d.z);

    float t1x = (min.x - ray.o.x) * r_inv_d.x;
    float t2x = (max.x - ray.o.x) * r_inv_d.x;
    float t1y = (min.y - ray.o.y) * r_inv_d.y;
    float t2y = (max.y - ray.o.y) * r_inv_d.y;
    float t1z = (min.z - ray.o.z) * r_inv_d.z;
    float t2z = (max.z - ray.o.z) * r_inv_d.z;

    float t1 = rt::max(rt::max(rt::min(t1x, t2x), rt::min(t1y, t2y)), rt::min(t1z, t2z));
    float t2 = rt::min(rt::min(rt::max(t1x, t2x), rt::max(t1y, t2y)), rt::max(t1z, t2z));

    return std::pair<float, float>(t1,t2);

}

bool BBox::isUnbound() const {
    /* TODO */ 
    float limit = FLT_MAX;
    return boxType == BoxType::full ||
    (min.x <= -limit && max.x >= limit) || (min.y <= -limit && max.y >= limit) || (min.z <= -limit &&
    max.z >= limit);
}



void BBox::clear() {
    max = Point(FLT_MAX, FLT_MAX, FLT_MAX);
    min = Point(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    boxType = BoxType::empty;
}

}
