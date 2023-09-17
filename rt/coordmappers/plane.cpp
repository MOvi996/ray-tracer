#include <rt/coordmappers/plane.h>

namespace rt {

PlaneCoordMapper::PlaneCoordMapper(const Vector& e1, const Vector& e2) : e1(e1), e2(e2) {
    /* TODO */
    if(dot(e1, e2) < epsilon)
        mat = Matrix::system(e1/e1.lensqr(), e2/e2.lensqr(), cross(e1, e2)).transpose();
    else
        mat = Matrix::system(e1, e2, cross(e1, e2)).invert();
}

Point PlaneCoordMapper::getCoords(const Intersection& hit) const {
    /* TODO */ 
    Point w_coords = hit.hitPoint();
    return mat * w_coords;
}

}