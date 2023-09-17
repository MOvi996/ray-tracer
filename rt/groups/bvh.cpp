#include <rt/groups/bvh.h>
#include <stack>
#include <queue>
#include <numeric>
#include <tuple>

namespace rt {

BVH::Node::Node()
{
    this->bbox = BBox::empty();
    this->num_prims = 0;
    this->prims = nullptr;
    this->leftChildId = 0;
}

BVH::Node::Node(BBox bbox, uint8_t num_prims,  uint32_t *prims, uint32_t leftChildId)
{
    this->bbox = bbox;
    this->num_prims = num_prims;
    this->prims = prims;
    this->leftChildId = leftChildId;   
}

void BVH::rebuildIndex() 
{
    /* TODO */ 
    // rebuildIndex() is called only once at the time of BVH construction
    if (this->nodes.empty())
    {
        typedef std::pair<uint32_t, std::vector<uint32_t>> Root;
        std::stack<Root> nodes_stack;
        std::vector<uint32_t> l_prims, r_prims, curr_prims;
        std::vector<BBox> bboxes(primitives.size());

        nodes.push_back(new Node(BBox::empty(), 0, nullptr, 0));

        uint32_t curr_node = 0;
        BBox curr_bbox;
        BBox curr_centroid_bbox;

        // append all primitives' bounding boxes to the vector boxes
        for (uint32_t i = 0; i < primitives.size(); i++)
        {
            bboxes[i] = primitives[i]->getBounds();
            if (bboxes[i].isUnbound())
            {
                unboundedPrims.push_back(i);
            }
            else
            {
                nodes[curr_node]->bbox.extend(bboxes[i]);
                curr_prims.push_back(i);
            }
        }

        nodes_stack.push(Root(curr_node, curr_prims));
        
        while (!nodes_stack.empty())
        {
            Root parent = nodes_stack.top();
            nodes_stack.pop();
            curr_node = parent.first;
            curr_prims = parent.second;

            curr_bbox = BBox::empty();
            curr_centroid_bbox = BBox::empty();

            for (uint32_t i = 0; i < curr_prims.size(); i++)
            {
                curr_bbox.extend(bboxes[curr_prims[i]]);
                curr_centroid_bbox.extend(bboxes[curr_prims[i]].centroid);
            }

            nodes[curr_node]->bbox = curr_bbox;

            //check whether splitting is required i.e. termination condition (prims < 3).
            if (curr_prims.size() < TERMINATION_COUNT)
            {
                nodes[curr_node]->num_prims = curr_prims.size();
                nodes[curr_node]->prims = new uint32_t[curr_prims.size()];
                for (uint32_t i = 0; i < curr_prims.size(); i++)
                {
                    nodes[curr_node]->prims[i] = curr_prims[i];
                }
            
            }
            else
            {
                rt_assert(curr_centroid_bbox.max >= curr_centroid_bbox.min);
                Vector diag = curr_centroid_bbox.diagonal();
                int split_axis = 0;
                float split_plane;
                if (diag.x > diag.y && diag.x > diag.z)
                {
                    split_axis = 1;
                    split_plane = (curr_centroid_bbox.min.x + curr_centroid_bbox.max.x) / 2.f;
                }
                else if (diag.y > diag.z)
                {
                    split_axis = 2;
                    split_plane = (curr_centroid_bbox.min.y + curr_centroid_bbox.max.y) / 2.f;
                }
                else
                {
                    split_axis = 3;
                    split_plane = (curr_centroid_bbox.min.z + curr_centroid_bbox.max.z) / 2.f;
                }
                
                // make children for the current parent node
                nodes[curr_node]->leftChildId = nodes.size();
                nodes.push_back(new Node());
                nodes.push_back(new Node());

                l_prims.clear();
                r_prims.clear();
                for (uint32_t i : curr_prims)
                {
                    if (
                        (split_axis == 1 && bboxes[i].centroid.x < split_plane) ||
                        (split_axis == 2 && bboxes[i].centroid.y < split_plane) ||
                        (split_axis == 3 && bboxes[i].centroid.z < split_plane))
                    {
                        l_prims.push_back(i);
                    }
                    else
                    {
                        r_prims.push_back(i);
                    }
                }

                nodes_stack.push(Root(nodes.size() - 2, l_prims));
                nodes_stack.push(Root(nodes.size() - 1, r_prims));
            }
        }
    }
    // Throw an exception if rebuildIndex is wrongly called (nodes are not empty)
    else UNREACHABLE;
}



BBox BVH::getBounds() const {
    /* TODO */ 
    if(nodes.empty())
    {
        BBox bbox = BBox::empty();
        BBox temp;
        for(uint32_t i = 0; i < primitives.size(); i++){
            temp = primitives[i]->getBounds();
            bbox.extend(temp);
        }
        return bbox;
        
    }
    rt_assert(!nodes.empty());
    return nodes[0]->bbox;
}

Intersection BVH::intersect(const Ray& ray, float tmin, float tmax) const {
    /* TODO */ 
    if(nodes.empty()) UNREACHABLE;
    
    std::stack<uint32_t> nodes_stack;
    nodes_stack.push(0);
    float prevBestDistance = tmax;
    uint32_t curr_node;
    float tmin_, tmax_;
    
    Intersection final_hit = Intersection::failure();
    Intersection curr_hit;
    std::pair<float, float> box_hit;
    
    for(uint32_t i : unboundedPrims)
    {
        curr_hit = primitives[i]->intersect(ray, tmin, prevBestDistance);
        if(curr_hit)
        {
            prevBestDistance = curr_hit.distance;
            final_hit = curr_hit;
        } 
    }
    while(!nodes_stack.empty())
    {
        curr_node = nodes_stack.top();
        nodes_stack.pop();

        if(nodes[curr_node]->num_prims>0)
        {
            for (uint32_t i = 0; i<nodes[curr_node]->num_prims; i++)
            {
                uint32_t prim_id = nodes[curr_node]->prims[i];
                curr_hit = primitives[prim_id]->intersect(ray, tmin, prevBestDistance);
                if (curr_hit)
                {
                    prevBestDistance = curr_hit.distance;
                    final_hit = curr_hit;
                }
            }
        }
        else if(curr_node > 0 || nodes[curr_node]->leftChildId != 0)
        {
            box_hit = nodes[curr_node]->bbox.intersect(ray);
            tmin_ = box_hit.first;
            tmax_ = box_hit.second;
            if (tmin_ <= tmax_ && tmin_ < prevBestDistance && tmax_ > 0)
            {
                nodes_stack.push(nodes[curr_node]->leftChildId);
                nodes_stack.push(nodes[curr_node]->leftChildId + 1);
            
            }
        }
    }
    return final_hit;
}

void BVH::add(Primitive* p) {
    /* TODO */ 
    primitives.push_back(p);
}

void BVH::setMaterial(Material* m) {
    /* TODO */ 
    for(auto &prim : primitives){
        prim->setMaterial(m);
    }
}

void BVH::setCoordMapper(CoordMapper* cm) {
    /* TODO */ 
    for(auto &prim : primitives){
        prim->setCoordMapper(cm);
    }
}

void BVH::serialize(BVH::Output& output) {
    // To implement this function:
    // - Call output.setNodeCount() with the number of nodes in the BVH
    /* TODO */
    // - Set the root node index using output.setRootId()
    /* TODO */
    // - Write each and every one of the BVH nodes to the output using output.writeNode()
    /* TODO */ NOT_IMPLEMENTED;
}
void BVH::deserialize(BVH::Input& input) {
    // To implement this function:
    // - Allocate and initialize input.getNodeCount() nodes
    /* TODO */
    // - Fill your nodes with input.readNode(index)
    /* TODO */
    // - Use the node at index input.getRootId() as the root node
    /* TODO */ NOT_IMPLEMENTED;
}

}