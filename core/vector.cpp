#include <core/scalar.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/homogeneouscoord.h>
#include <core/assert.h>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace rt {

Vector::Vector(float x, float y, float z)
{
    /* TODO */
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(const HomogeneousCoord& coord)
{
    /* TODO */
    if(coord[3]!=0){
        this->x = coord[0]/coord[3];
        this->y = coord[1]/coord[3];
        this->z = coord[2]/coord[3];
    }
    else{
        this->x = coord[0];
        this->y = coord[1];
        this->z = coord[2];
    }
    
}

Vector Vector::operator + (const Vector& b) const {
    /* TODO */
    return Vector(x+b.x, y+b.y, z+b.z); 
}

Vector Vector::operator - (const Vector& b) const {
    /* TODO */ 
    return Vector(x-b.x, y-b.y, z-b.z); 
}

Vector Vector::operator - () const {
    /* TODO */ 
    return Vector(-x, -y, -z);
}

Vector Vector::normalize() const {
    /* TODO */ 
    return Vector(x/this->length(), y/this->length(), z/this->length());
}

Vector operator * (float scalar, const Vector& b) {
    /* TODO */ 
    return Vector(b.x*scalar, b.y*scalar, b.z*scalar);
}

Vector operator * (const Vector& a, float scalar) {
    /* TODO */ 
    return Vector(a.x*scalar, a.y*scalar, a.z*scalar);
}

Vector operator / (const Vector& a, float scalar) {
    /* TODO */ 
    //assert(fabsf(scalar)>epsilon);
    return Vector(a.x/scalar, a.y/scalar, a.z/scalar);
}

Vector cross(const Vector& a, const Vector& b) {
    /* TODO */ 
    return Vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

float dot(const Vector& a, const Vector& b) {
    /* TODO */ 
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

float Vector::lensqr() const {
    /* TODO */ 
    return x*x + y*y + z*z;
}

float Vector::length() const {
    /* TODO */ 
    return sqrt(x*x + y*y + z*z);
}


bool Vector::operator == (const Vector& b) const {
    /* TODO */ 
    return (fabsf(x - b.x) < epsilon) && (fabsf(y - b.y) < epsilon) && (fabsf(z - b.z) < epsilon);
}

bool Vector::operator != (const Vector& b) const {
    /* TODO */ 
    return (fabsf(x - b.x) >= epsilon) || (fabsf(y - b.y) >= epsilon) || (fabsf(z - b.z) >= epsilon);
}

Vector min(const Vector& a, const Vector& b) {
    /* TODO */ 
    float min_x = std::min(a.x, b.x);
    float min_y = std::min(a.y, b.y);
    float min_z = std::min(a.z, b.z);

    return Vector(min_x,min_y,min_z);

}

Vector max(const Vector& a, const Vector& b) {
    /* TODO */ 
    float max_x = std::max(a.x, b.x);
    float max_y = std::max(a.y, b.y);
    float max_z = std::max(a.z, b.z);

    return Vector(max_x,max_y,max_z);
}

Point operator + (const Point& a, const Vector& b) {
    /* TODO */
    return Point(a.x+b.x, a.y+b.y, a.z+b.z);
}

Point operator + (const Vector& a, const Point& b) {
    /* TODO */
    return b+a;
}

Point operator - (const Point& a, const Vector& b) {
    /* TODO */
    return Point(a.x-b.x, a.y-b.y, a.z-b.z);
}

Point operator * (const HomogeneousCoord& scale, const Point& p) {
    /* TODO */ NOT_IMPLEMENTED;
}

}
