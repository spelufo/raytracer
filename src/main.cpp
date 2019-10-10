#include <stdio.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "basics.cpp"
#include "math.cpp"
#include "color.cpp"
#include "raytrace.cpp"

namespace {
	Color3f sky_color = {0.5f, 0.7f, 1.0f};
	Color3f fully_saturated_color = Color3fs::white;

	Material materials[] = {
		{0.0f, Color3f{0.8f, 0.8f, 0.8f}},
		{1.0f, Color3f{0.4f, 0.3f, 0.3f}}, // ground material
		{1.0f, Color3f{0.9f, 0.5f, 0.5f}},
		{0.7f, Color3f{0.7f, 0.8f, 0.2f}},
	};

	Sphere spheres[] = {
		{Point{ 0.0f,  0.0f, -250.f}, 250.f, 1}, // ground sphere
		{Point{ 0.0f,  0.0f,  0.0f}, 1.0f, 0},   // origin sphere
		{Point{-0.8f,  0.0f, 3.7f}, 1.5f, 2},
		{Point{ 1.0f,  0.3f, 1.0f}, 0.7f, 3},
	};

	World world = { len(materials), materials, len(spheres), spheres, sky_color };
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "usage: raytracer OUTPUT_IMAGE_PATH\n");
		return 1;
	}

	f32 width = 2.0f, height = 3.0f;
	f32 resolution = 200.0f; // px per meters

	Frame eye_frame = {
		Point{    0.0f, 10.0f,  2.0f},
		Vector3f{-0.25f, 0.0f,  0.0f},
		Vector3f{ 0.0f, 0.0f,  0.25f},
		Vector3f{ 0.0f, 1.0f,  0.0f},
	};

	int img_width = width * resolution;
	int img_height = height * resolution;
	Color4b *img_data = new Color4b[img_height * img_width];  // allocate

	printf("raytracing... %dx%d\n", img_width, img_height);
	render(&world, &eye_frame, img_data, width, height, resolution, fully_saturated_color);

	stbi_write_png(argv[1], img_width, img_height, 4, img_data, img_width*sizeof(Color4b));
	delete[] img_data;
	return 0;
}