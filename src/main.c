#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "basics.c"
#include "math.c"
#include "color.c"
#include "raytrace.c"

namespace {
	Color4f sky_color = {0.6f, 0.9f, 1.0f, 1.0f};

	Sphere spheres[] = {
		Sphere{Point{-1.0f, 0.0f, -3.0f}, 0.5f, Color4f{1.0f, 0.5f, 0.0f, 1.0f}},
		Sphere{Point{0.75f, 0.0f, -2.5f}, 0.3f, Color4f{1.0f, 0.0f, 0.0f, 1.0f}},
		Sphere{Point{ 1.0f, 0.7f, -3.0f}, 0.4f, Color4f{0.4f, 0.5f, 1.0f, 1.0f}},
		Sphere{Point{ 1.0f, -0.7f, -3.0f}, 0.4f, Color4f{0.4f, 0.5f, 0.0f, 1.0f}},
	};	
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "usage: raytracer OUTPUT_IMAGE_PATH\n");
		return 1;
	}

	float width = 1.5f, height = 1.0f;
	float resolution = 400.0f; // px per meters

	int img_width = width * resolution;
	int img_height = height * resolution;
	printf("raytracing... %dx%d\n", img_width, img_height);
	Color4b *img_data = new Color4b[img_height * img_width];

	auto eye_ray = Ray{Point{0.0f, 0.0f, 0.0f}, Vector3f{0.0f, 0.0f, -1.0f}};
	auto screen_p = add(eye_ray.p, eye_ray.n);

	for (int y = 0; y < img_height; ++y) {
		for (int x = 0; x < img_width; ++x) {
			Vector3f pix_screen_v = {
				(float)x/(float)resolution - width/2.0f,
				(float)y/(float)resolution - height/2.0f,
				0.0f,
			};
			Ray pix_ray = ray_to_from(add(screen_p, pix_screen_v), eye_ray.p);

			float sphere_nearest_dist = 1000.0f;
			Sphere *sphere_nearest = NULL;
			
			each (sphere, spheres) {
				float d = intersect(sphere, pix_ray);
				if (d > 0.0f && d < sphere_nearest_dist) {
					sphere_nearest = sphere;
					sphere_nearest_dist = d;
				}
			}

			Color4f c = sky_color;
			if (sphere_nearest) {
				c = sphere_nearest->color;
			}

			img_data[y*img_width + x] = color_4f_to_4b(c);
		}
	}

	stbi_write_png(argv[1], img_width, img_height, 4, img_data, img_width*sizeof(Color4b));
	delete[] img_data;
	return 0;
}