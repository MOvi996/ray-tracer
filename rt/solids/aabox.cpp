#include <rt/solids/aabox.h>
#include <core/assert.h>
namespace rt {

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material) : Solid(texMapper, material)
{
    /* TODO */
    //Box ABCD

    this->corners[0] = min(corner1, corner2);    //B0
    this->corners[1] = max(corner1, corner2);    //B1
    this->material = material;

}

BBox AABox::getBounds() const {
    /* TODO */ 
    Point b0 = min(corners[0], corners[1]);
    Point b1 = max(corners[0], corners[1]);
    return BBox(b0, b1);
}

Solid::Sample AABox::sample() const {
    NOT_IMPLEMENTED;
}

float AABox::getArea() const {
    /* TODO */ 
    Vector diag = corners[1] - corners[0];
    return 2 * (diag.x * diag.y + diag.y * diag.z + diag.z * diag.x);
}

Intersection AABox::intersect(const Ray& ray, float tmin, float tmax) const {
    /* TODO */ 
    Point c1 = corners[0];
    Point c2 = corners[1];
    
    Vector r_inv_d = Vector(1.f / ray.d.x, 1.f / ray.d.y, 1.f / ray.d.z);

    float t1x = (c1.x - ray.o.x) * r_inv_d.x;
    float t2x = (c2.x - ray.o.x) * r_inv_d.x;
    float t1y = (c1.y - ray.o.y) * r_inv_d.y;
    float t2y = (c2.y - ray.o.y) * r_inv_d.y;
    float t1z = (c1.z - ray.o.z) * r_inv_d.z;
    float t2z = (c2.z - ray.o.z) * r_inv_d.z;

    float tmin_ = max(max(min(t1x, t2x), min(t1y, t2y)), min(t1z, t2z));
    float tmax_ = min(min(max(t1x, t2x), max(t1y, t2y)), max(t1z, t2z));

    if (tmax_ < tmin_ || tmin_ > tmax_ || tmin_ < 0 || tmin_ < tmin || tmin_ > tmax)
    {
        return Intersection::failure();
    }

    // find hit surface's direction in x, y and z axis and thus its normal. Note that for axis aligned
    // boxes, normal has only one non-zero component. Its can be positive or negative depending on the
    // face of the box.
    Point p = ray.getPoint(tmin_);
    Vector c1_p = p - c1;
    Vector c2_p = p - c2;

    Vector normal_;
    float dir_;
    if (fabsf(c1_p.x) < epsilon || fabsf(c2_p.x) < epsilon)
    {
        dir_ = fabsf(c2_p.x) < epsilon ? c1_p.x - c2_p.x : c2_p.x - c1_p.x;
        normal_ = Vector((dir_ > 0) - (dir_ < 0), 0, 0);
    }
    else if (fabsf(c1_p.y) < epsilon || fabsf(c2_p.y) < epsilon)
    {
        dir_ = fabsf(c2_p.y) < epsilon ? c1_p.y - c2_p.y : c2_p.y - c1_p.y;
        normal_ = Vector(0, (dir_ > 0) - (dir_ < 0), 0);
    }
    else if (fabsf(c1_p.z) < epsilon || fabsf(c2_p.z) < epsilon)
    {
        dir_ = fabsf(c2_p.z) < epsilon ? c1_p.z - c2_p.z : c2_p.z - c1_p.z;
        normal_ = Vector(0, 0, (dir_ > 0) - (dir_ < 0));
    }
    else
    {
        return Intersection::failure();
    }

    return Intersection(tmin_, ray, this, normal_, p);
}

}
