#ifndef RAY_H
#define RAY_H
#include <glm.hpp>
#include "Materials.hpp"

struct Ray
{
    glm::vec3 orig;
    glm::vec3 dir;

    Ray() {};

    Ray(glm::vec3 origin, glm::vec3 direction):
    orig(origin), dir(direction){}

    glm::vec3 at(float t)
    {
        return orig + t * dir;
    };
};

struct hitInfo {
    glm::vec3 normal;
    glm::vec3 point;
    float t;
    bool front_face;

    void set_face_normal(const Ray& r, const glm::vec3& outward_normal) {
        front_face = glm::dot(r.dir, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};



#endif