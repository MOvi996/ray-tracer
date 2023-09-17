#include <rt/groups/simplegroup.h>

namespace rt {

BBox SimpleGroup::getBounds() const {
    /* TODO */ 
    BBox bounds = BBox::empty();

    for(uint32_t i=0; i<primitives.size(); i++){
        bounds.extend(primitives[i]->getBounds());
    }
    return bounds;
}

Intersection SimpleGroup::intersect(const Ray& ray, float tmin, float tmax) const {
    /* TODO */ 
    Intersection hit = Intersection::failure();
    float prevBestDist = tmax;

    for(auto &prim : primitives){
    Intersection temp = prim->intersect(ray, tmin, prevBestDist);
        if(temp && temp.distance < prevBestDist){
            prevBestDist = temp.distance;
            hit = temp;
        }
    }
    return hit;

}

void SimpleGroup::rebuildIndex() {
    //do nothing
}

void SimpleGroup::add(Primitive* p) {
    /* TODO */ 
    primitives.push_back(p);
}

void SimpleGroup::setMaterial(Material* m) {
    /* TODO */ 
    for(auto &prim : primitives){
        prim->setMaterial(m);
    }
}

void SimpleGroup::setCoordMapper(CoordMapper* cm) {
    /* TODO */ 
    for(auto &prim : primitives){
        prim->setCoordMapper(cm);
    }
}



}
