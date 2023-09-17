#include <core/homogeneouscoord.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/assert.h>
#include <core/scalar.h>

namespace rt {

HomogeneousCoord::HomogeneousCoord(float x, float y, float z, float w) {
    /* TODO */
    // this->x = x;
    // this->y = y;
    // this->z = z;
    // this->w = w;
    this->mat[0] = x;
    this->mat[1] = y;
    this->mat[2] = z;
    this->mat[3] = w;
}

HomogeneousCoord::HomogeneousCoord(const Point& p) {
    /* TODO */ 
    this->mat[0] = p.x;
    this->mat[1] = p.y;
    this->mat[2] = p.z;
    this->mat[3] = 1;
}

HomogeneousCoord::HomogeneousCoord(const Vector& vec) {
    /* TODO */ 
    this->mat[0] = vec.x;
    this->mat[1] = vec.y;
    this->mat[2] = vec.z;
    this->mat[3] = 0;
}

float& HomogeneousCoord::operator [] (int idx) {
    /* TODO */ 
    rt_assert(idx<4);
    return mat[idx];
}

float HomogeneousCoord::operator [] (int idx) const {
    /* TODO */ 
    rt_assert(idx<4);
    return mat[idx];
}

HomogeneousCoord HomogeneousCoord::operator + (const HomogeneousCoord& b) const {
    /* TODO */ 
    return HomogeneousCoord(mat[0]+b[0], mat[1]+b[1], mat[2]+b[2], mat[3]+b[3]);
}

HomogeneousCoord HomogeneousCoord::operator - (const HomogeneousCoord& b) const {
    /* TODO */ 
    return HomogeneousCoord(mat[0]-b[0], mat[1]-b[1], mat[2]-b[2], mat[3]-b[3]);
}

HomogeneousCoord HomogeneousCoord::operator * (const HomogeneousCoord& b) const {
    /* TODO */ 
    return HomogeneousCoord(mat[0]*b[0], mat[1]*b[1], mat[2]*b[2], mat[3]*b[3]);
}

HomogeneousCoord HomogeneousCoord::operator / (const HomogeneousCoord& b) const {
    /* TODO */ 
    return HomogeneousCoord(mat[0]/b[0], mat[1]/b[1], mat[2]/b[2], mat[3]/b[3]);
}

HomogeneousCoord operator * (float scalar, const HomogeneousCoord& b) {
    /* TODO */ 
    return HomogeneousCoord(b[0]*scalar, b[1]*scalar, b[2]*scalar, b[3]*scalar);
}

HomogeneousCoord operator * (const HomogeneousCoord& a, float scalar) {
    /* TODO */ 
    return HomogeneousCoord(a[0]*scalar, a[1]*scalar, a[2]*scalar, a[3]*scalar);
}

HomogeneousCoord operator / (const HomogeneousCoord& a, float scalar) {
    /* TODO */ 
    return HomogeneousCoord(a[0]/scalar, a[1]/scalar, a[2]/scalar, a[3]/scalar);
}

float dot(const HomogeneousCoord& a, const HomogeneousCoord& b) {
    /* TODO */ 
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2]+a[3]*b[3];

}

HomogeneousCoord HomogeneousCoord::operator - () const {
    /* TODO */ 
    return HomogeneousCoord(-mat[0], -mat[1], -mat[2], -mat[3]);
;
}

bool HomogeneousCoord::operator == (const HomogeneousCoord& b) const {
    /* TODO */ 
    return (fabsf(mat[0] - b[0]) < epsilon) && (fabsf(mat[1] - b[1]) < epsilon) && (fabsf(mat[2] - b[2]) < epsilon) && (fabsf(mat[3]-b[3]) < epsilon);
}

bool HomogeneousCoord::operator != (const HomogeneousCoord& b) const {
    /* TODO */ 
    return (fabsf(mat[0] - b[0]) >= epsilon) || (fabsf(mat[1] - b[1]) >= epsilon) || (fabsf(mat[2] - b[2]) >= epsilon) || (fabsf(mat[3] - b[3]) >= epsilon);
}

HomogeneousCoord min(const HomogeneousCoord& a, const HomogeneousCoord& b) {
    /* TODO */ 
    return HomogeneousCoord(std::min(a[0], b[0]),
                            std::min(a[1], b[1]),
                            std::min(a[2], b[2]),
                            std::min(a[3], b[3]));
}

HomogeneousCoord max(const HomogeneousCoord& a, const HomogeneousCoord& b) {
    /* TODO */ 
    return HomogeneousCoord(std::max(a[0], b[0]),
                            std::max(a[1], b[1]),
                            std::max(a[2], b[2]),
                            std::max(a[3], b[3]));
}

}