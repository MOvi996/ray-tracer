#include <rt/solids/quad.h>
#include <core/random.h>
#include <core/interpolate.h>



namespace rt {

Quad::Quad(const Point& origin, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
    /* TODO */
    this->span1 = span1;
    this->span2 = span2;

    this->vertices[0] = origin;                         //A
    this->vertices[1] = origin + span1;                 //B
    this->vertices[2] = this->vertices[1] + span2;      //C
    this->vertices[3] = origin + span2;                 //D

    this->sides[0] = vertices[1] - vertices[0];     //AB
    this->sides[1] = vertices[2] - vertices[1];     //BC
    this->sides[2] = vertices[3] - vertices[2];     //CD
    this->sides[3] = vertices[3] - vertices[0];     //AD

    this->normal = cross(this->sides[0], this->sides[3]).normalize();
    this->material = material;
}   

BBox Quad::getBounds() const {
    /* TODO */ 
    Point b0 = min(min(min(vertices[0] , vertices[1]), vertices[2]), vertices[3]);
    Point b1 = max(max(max(vertices[0] , vertices[1]), vertices[2]), vertices[3]);
    return BBox(b0, b1);
}

Intersection Quad::intersect(const Ray& ray, float tmin, float tmax) const {
    /* TODO */ 
    // let us visualize our quadrilateral ABCD as a combination of two triangles ABD and BCD 
    // separated by the diagonal BD. We can then use moller-trumbore algorithm to detect ray 
    // intersection. While checking on one of the two triangles, if u,v<0 or u,v>1 , then the 
    // point lies outside both triangles, and thus the quadrilateral. But if u+v>1, then the
    // point lies outside the triangle in question but not necessarily the quadrilateral, hence 
    // we then need to check on the other triangle. (Lagae, Dutre 2004)  

    // checking on triangle ABD
    Vector AB = sides[0];
    Vector AD = sides[3];
    // Vector CB = - sides[1];
    // Vector CD = sides[2];

    float t, u, v;

    Vector cross_D_AD = cross(ray.d, AD);
    float det = dot(cross_D_AD, AB);

    if(fabsf(det) < epsilon){
        return Intersection::failure();         //ray parallel to quadrilateral
    }

    float inv_det = 1.f / det;
    Vector o_v0 = ray.o - vertices[0];

    u = dot(o_v0, cross_D_AD) * inv_det;

    if(u<0 || u > 1){
        return Intersection::failure();         //pt lies outside triangle
    }

    Vector cross_ov0_AB = cross(o_v0, AB);
    v = dot(ray.d, cross_ov0_AB)*inv_det;

    if(v < 0 || v>1){
        return Intersection::failure();         //pt lies outside triangle
    }
    
    t = dot(AD, cross_ov0_AB)*inv_det;

    if(t > tmin && t < tmax){
        Point p(u, v, 0);
        
        Vector normal_ = normal;
        return Intersection(t, ray, this, normal_.normalize(), p);
    }
    return Intersection::failure();
}

Solid::Sample Quad::sample() const {
    /* TODO */ 
    float a = random();
    float b = random();

    return Solid::Sample {
        vertices[0] + sides[0] * a + sides[3] * b,
        this->normal
        };
}

float Quad::getArea() const {
    /* TODO */ 
    Vector base = vertices[1] - vertices[0];
    Vector side_l = vertices[3] - vertices[0];
    Vector projection = dot(base, side_l)*base;
    Vector perpendicular = side_l - projection;

    return base.length() * perpendicular.length();

}


}
