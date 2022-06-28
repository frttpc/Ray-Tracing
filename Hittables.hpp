#ifndef HITTABLE_H
#define HITTABLE_H
#include <glm.hpp>
#include "Rays.hpp"
#include <vector>

using namespace std;

class hittable
{
public:
    virtual bool hit(Ray r, hitInfo &info) { return false; };

    friend class HittableList;
};

class HittableList
{
public:
    std::vector<shared_ptr<hittable>> objects;

    HittableList() {}
    void add(shared_ptr<hittable> object);

    bool hit(Ray& ray, hitInfo& info) 
    {
        hitInfo tempRec;
        float minDistance = std::numeric_limits<float>::max();
        bool hit_anything = false;

        for (const auto& object : objects) {
            if (object->hit(ray, tempRec)) {
                hit_anything = true;
                const float distance = glm::distance(tempRec.point, ray.orig);
                if (distance < minDistance) {
                    minDistance = distance;
                    info = tempRec;
                }
            }
        }

        return hit_anything;
    };
};

void HittableList::add(shared_ptr<hittable> object)
{
    objects.push_back(object);
};

#endif