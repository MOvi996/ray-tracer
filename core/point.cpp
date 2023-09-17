#include <core/point.h>
#include <core/homogeneouscoord.h>
#include <core/scalar.h>
#include <core/assert.h>
#include <core/vector.h>

namespace rt {

Point::Point(float x, float y, float z)
{
    /* TODO */
    this->x=x;
    this->y=y;
    this->z=z;
}

Point::Point(const HomogeneousCoord& coord)
{
    /* TODO */
    if(coord[3]!=1){
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

Vector Point::operator - (const Point& b) const {
    /* TODO */
    return Vector(x-b.x, y-b.y, z-b.z);
}

bool Point::operator == (const Point& b) const {
    /* TODO */ 
    return (fabsf(x - b.x) < epsilon) && (fabsf(y - b.y) < epsilon) && (fabsf(z - b.z) < epsilon);
}

bool Point::operator > (const Point& b) const {
    /* TODO */ 
    return (x > b.x) && (y > b.y) && (z > b.z);
}

bool Point::operator < (const Point& b) const {
    /* TODO */ 
    return (x < b.x) && (y < b.y) && (z < b.z);
}

bool Point::operator >= (const Point& b) const {
    /* TODO */ 
    return (x >= b.x - epsilon) && (y >= b.y - epsilon) && (z >= b.z - epsilon);
}

bool Point::operator <= (const Point& b) const {
    /* TODO */ 
    return (x <= b.x + epsilon) && (y <= b.y+epsilon) && (z <= b.z+epsilon);
}


bool Point::operator != (const Point& b) const {
    /* TODO */ 
    return (fabsf(x - b.x) >= epsilon) || (fabsf(y - b.y) >= epsilon) || (fabsf(z - b.z) >= epsilon);
}

Point operator * (float scalar, const Point& b) {
    /* TODO */ 
    return Point(scalar*b.x, scalar*b.y, scalar*b.z);
}


Point operator * (const Point& a, float scalar) {
    /* TODO */ 
    return Point(scalar*a.x, scalar*a.y, scalar*a.z);;
}

Point min(const Point& a, const Point& b) {
    /* TODO */ 
    return Point(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point max(const Point& a, const Point& b) {
    /* TODO */ 
    return Point(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));;

}

}
