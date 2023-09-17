#include <rt/primmod/instance.h>

namespace rt {

Instance::Instance(Primitive* content)
{
    /* TODO */
    prim = content;
    transform = Matrix::identity();
}

Primitive* Instance::content() {
    /* TODO */ 
    return prim;
}

void Instance::reset() {
    /* TODO */ 
    transform = Matrix::identity();
}

void Instance::translate(const Vector& t) {
    /* TODO */ 
    Matrix M = Matrix::identity();
    M[0][3] = t.x;
    M[1][3] = t.y;
    M[2][3] = t.z;

    transform = product(M, transform);
}

void Instance::rotate(const Vector& nnaxis, float angle) {
    /* TODO */ 
    Vector a = nnaxis.normalize();
    Vector s, t;

    if(a.x < a.y && a.x < a.z){
        s = Vector(0, -a.z, a.y);
    }
    else if (a.y > a.z){
        s = Vector(-a.z, 0, a.x);
    }
    else s = Vector(-a.y, a.x, 0);

    s = s.normalize();

    t = cross(a, s).normalize();

    Matrix M = Matrix::system(a, s, t);
    float sine = std::sin(angle);
    float cosine = std::cos(angle);

    Matrix rot = Matrix::identity();
    rot[1][1] = cosine;
    rot[1][2] = -sine;
    rot[2][1] = sine;
    rot[2][2] = cosine;

    transform = product(product(M, product(rot, M.transpose())), transform);    
}

void Instance::scale(float f) {
    /* TODO */ 
    for(int i = 0; i<3; i++) transform[i][i] *= f;
}

void Instance::scale(const Vector& s) {
    /* TODO */ 
    transform[0][0] *= s.x;
    transform[1][1] *= s.y;
    transform[2][2] *= s.z;
}

void Instance::setMaterial(Material* m) {
    /* TODO */ 
    this->prim->setMaterial(m);
}

void Instance::setCoordMapper(CoordMapper* cm) {
    /* TODO */ 
    this->prim->setCoordMapper(cm);
}

Intersection Instance::intersect(const Ray& ray, float tmin, float tmax) const {
    /* TODO */ 
    Matrix transform_inv = transform.invert();

    Point ro_transformed = transform_inv*ray.o;
    Vector rd_transformed = (transform_inv*ray.d).normalize();
    Ray r_transformed = Ray(ro_transformed, rd_transformed);
        
    //now check for intersection with prim
    float prevBestDistance = tmax;
    Intersection temp = prim->intersect(r_transformed, 0, prevBestDistance);
    
    if(temp){
        if(temp.distance < prevBestDistance){
            //now transform back distance, ray and normal
            temp.ray = ray;
            temp.normal_ = (transform_inv.transpose() * temp.normal_).normalize();
            temp.distance = (transform * r_transformed.getPoint(temp.distance) - temp.ray.o).length();
            return temp;
        }
    }
    return Intersection::failure();
    
}

BBox Instance::getBounds() const {
    /* TODO */ 
    BBox A = prim->getBounds();
    
    if(A.boxType == BoxType::full or A.boxType == BoxType::empty) return A;

    BBox B; //Transformed matrix
    B.extend(transform * Point(A.min.x, A.min.y, A.min.z));
    B.extend(transform * Point(A.min.x, A.min.y, A.max.z));
    B.extend(transform * Point(A.min.x, A.max.y, A.min.z));
    B.extend(transform * Point(A.max.x, A.min.y, A.min.z));
    B.extend(transform * Point(A.min.x, A.max.y, A.max.z));
    B.extend(transform * Point(A.max.x, A.min.y, A.max.z));
    B.extend(transform * Point(A.max.x, A.max.y, A.min.z));
    B.extend(transform * Point(A.max.x, A.max.y, A.max.z));

    return B;
    


}

}