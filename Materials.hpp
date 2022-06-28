#pragma once
#ifndef MATERIAL_H
#define	MATERIAL_H
#include "glm.hpp"
#include "Rays.hpp"
#include "Hittables.hpp"
#include "Utilities.hpp"


class material {
public:
	virtual bool scatter(const Ray& ray_in, const hitInfo& rec, glm::vec3& attenuation, Ray& scattered) const = 0;
};

class lambertian : public material {
public:

	glm::vec3 albedo;

	lambertian(const glm::vec3& a) : albedo(a) {}

	virtual bool scatter(const Ray& ray_in, const hitInfo& rec, glm::vec3& attenuation, Ray& scattered) const {
		glm::vec3 scatter_dir = rec.normal + glm::normalize(glm::vec3(randFloat(), randFloat(), randFloat()));

		if (glm::abs(scatter_dir.x) < 1e-8 && glm::abs(scatter_dir.y) < 1e-8 && glm::abs(scatter_dir.z) < 1e-8)
			scatter_dir = rec.normal;

		scattered = Ray(rec.point, scatter_dir);
		attenuation = albedo;

		return true;
	}
};

class metal : public material {
public:
	glm::vec3 albedo;

	metal(const glm::vec3 & a) : albedo(a) {}

	virtual bool scatter(const Ray& r_in, const hitInfo& rec, glm::vec3 attenuation, Ray& scattered) const {
		glm::vec3 reflected = glm::reflect(glm::normalize(r_in.dir), rec.normal);
		scattered = Ray(rec.point, reflected);
		attenuation = albedo;
		return (glm::dot(scattered.dir, rec.normal) > 0);
	}
};
#endif // !MATERIAL_H