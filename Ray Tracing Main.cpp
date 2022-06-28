#include <iostream>
#include <glm.hpp>
#include <fstream>
#include <cmath>
#include "Rays.hpp"
#include "Utilities.hpp"
#include "Hittables.hpp"
#include "Spheres.hpp"
#include "Materials.hpp"

using namespace std;


glm::vec3 rayColor(Ray &ray, HittableList & world) {
	
	hitInfo info;

	if (world.hit(ray, info)) {
		const glm::vec3 normal = (glm::normalize(info.normal) + glm::vec3(1)) * 0.5f;

		return normal;
	}


	float y = glm::normalize(ray.dir).y;
	float t = (y + 1) * 0.5;

	return t*glm::vec3(1) + (1.0f-t)*glm::vec3(.9,.3,.9);
}


int main() {

	// Image
	const float aspect_ratio = 16.0 / 9.0;
	const int image_width = 800, image_height = 800 / aspect_ratio;

	// Scene
	HittableList scene;

	scene.add(make_shared<sphere>(glm::vec3(0, 0, -1), 0.5));
	scene.add(make_shared<sphere>(glm::vec3(0, -100.5, -1), 100));

	// Camera1
	glm::vec3 origin(1,0,-1);
	glm::vec3 horizontal(1,0,0);
	glm::vec3 vertical(0,1,0);

	const float viewport_height = 2.0;
    const float viewport_width = aspect_ratio * viewport_height;
    const float focal_length = 1.0;

	const glm::vec3 left_corner = origin - glm::vec3(viewport_width * .5f, viewport_height * .5f, focal_length);

	
	// Output
	ofstream output1{ "output.ppm" };
	output1 << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	// Render
	for (int y = image_height - 1; y >= 0; --y) {

		cerr << "\rScanlines remaining: " << y << ' ' << flush;

		for (int x = 0; x < image_width; ++x) {


			float u = ((x + randFloat()) / (image_width - 1.0)) * viewport_width;
			float v = ((y + randFloat()) / (image_height - 1.0)) * viewport_height;
			glm::vec3 point = left_corner + v * vertical + u * horizontal;
			glm::vec3 dir = point - origin;
			Ray ray(origin, dir);

			glm::vec3 color = rayColor(ray, scene);

			writeImage(color, output1);
		}

	}
	cerr << "\nDone.\n";
	output1.close(); 
	
}