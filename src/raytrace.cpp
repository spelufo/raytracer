#ifdef INCLUDED_RAYTRACE
#  error duplicate include: RAYTRACE
#endif
#define INCLUDED_RAYTRACE


struct Frame {
	Point p;
	Vector3f x, y, z;
};


struct Material {
	Color3f color;
};


struct Sphere {
	Point p;
	f32 radius;
	u32 material_id;
};

internal Vector3f surface_normal(Sphere *sphere, Point p) {
	return normalize(sub(p, sphere->p));
}

internal f32 intersect(Sphere *sphere, Ray ray) {
	Vector3f rayp_sphere = sub(ray.p, sphere->p);
	f32 a2 = square(ray.n);
	f32 b2 = dot(ray.n, rayp_sphere);
	f32 c2 = square(rayp_sphere) - square(sphere->radius);
	f32 arg_sqrt = square(b2) - a2 * c2;
	if (arg_sqrt < 0) return max_f32;
	f32 t = - (b2 + sqrtf(arg_sqrt)) / a2;
	return t > 0 ? t : max_f32;
}


struct World {
	u32 materials_count;
	Material *materials;

	u32 spheres_count;
	Sphere *spheres;
	
	Color3f sky_color;
};


void render(World *world, Frame *eye_frame, Color4b *img_data, f32 width, f32 height, f32 resolution, Color3f fully_saturated_color) {
	int img_width = width * resolution;
	int img_height = height * resolution;
	Point screen_p = sub(eye_frame->p, eye_frame->z);

	for (int y = 0; y < img_height; ++y) {
		for (int x = 0; x < img_width; ++x) {
			Vector3f screen_vx = mul((f32)x/(f32)resolution - width/2.0f, eye_frame->x);
			Vector3f screen_vy = mul((f32)y/(f32)resolution - height/2.0f, eye_frame->y);
			Vector3f screen_v = add(screen_vx, screen_vy);
			Point pixel_p = add(screen_p, screen_v);
			Ray pix_ray = ray_to_from(pixel_p, eye_frame->p);

			f32 sphere_nearest_dist = max_f32;
			Sphere *sphere_nearest = NULL;
			
			for (Sphere *sphere = world->spheres; sphere < world->spheres + world->spheres_count; ++sphere) {
				f32 d = intersect(sphere, pix_ray);
				if (d > 0.0f && d < sphere_nearest_dist) {
					sphere_nearest = sphere;
					sphere_nearest_dist = d;
				}
			}

			Color3f c = world->sky_color;
			if (sphere_nearest) {
				c = world->materials[sphere_nearest->material_id].color;
			}

			img_data[(img_height - 1 - y)*img_width + x] = color_3f_to_4b(c, fully_saturated_color);
		}
	}
}