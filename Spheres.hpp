#ifndef SPHERE_H
#define SPHERE_H
#include <iostream>
#include <glm.hpp>
#include "Hittables.hpp"
#include "Rays.hpp"

class sphere : public hittable
{
public:
    glm::vec3 center;
    float radius;
    shared_ptr<material> mat_ptr;

    sphere(glm::vec3 cen, float r):center(cen), radius(r){};
    bool hit(Ray ray, hitInfo& info) ;
};

bool sphere::hit(Ray ray, hitInfo& info) {
    
    glm::vec3 w = ray.orig - center;
    float a = glm::dot(ray.dir, ray.dir);
    float b = 2.0f * glm::dot(ray.dir, w);
    float c = glm::dot(w,w) - radius*radius;

    float discriminant = b*b - 4*a*c;

    if(discriminant <= 0) {
        return false;
    }

    const float t = (-b - sqrt(discriminant)) / (2.0 * a);
  
    info.point = ray.at(info.t);
    info.normal = info.point - center;
    info.t = t;

    glm::vec3 outward_normal = (info.point - center) / radius;
    info.set_face_normal(ray, outward_normal);

    return t > 0;
}

#endif