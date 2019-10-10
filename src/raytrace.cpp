#ifdef INCLUDED_RAYTRACE
#  error duplicate include: RAYTRACE
#endif
#define INCLUDED_RAYTRACE


namespace {
	const int max_ray_bounces = 100;
}

struct Frame {
	Point p;
	Vector3f x, y, z;
};


struct Material {
	f32 diffuse;
	Color3f albedo;
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
	f32 a2 = square(ray.d);
	f32 b2 = dot(ray.d, rayp_sphere);
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

internal Color3f bounce_attenuation(Material *mat, f32 iangle, f32 oangle) {
	return mat->albedo;
}

internal Color3f trace_ray(World *world, Ray ray) {
	Color3f attenuation = Color3fs::white;
	for (int bounce = 0; bounce < max_ray_bounces; ++bounce) {

		f32 sphere_nearest_dist = max_f32;
		Sphere *sphere_nearest = NULL;		
		for (Sphere *sphere = world->spheres; sphere < world->spheres + world->spheres_count; ++sphere) {
			f32 d = intersect(sphere, ray);
			if (d > 0.0000001f && d < sphere_nearest_dist) {
				sphere_nearest = sphere;
				sphere_nearest_dist = d;
			}
		}

		if (sphere_nearest == NULL) {
			Color3f sky_color = lerp(0.5f*(normalize(ray.d).y + 1.0f), Color3fs::white, world->sky_color);
			return mul(attenuation, sky_color);
		}

		Ray hit = ray_to_from(ray.p, add(ray.p, mul(sphere_nearest_dist, ray.d)));
		Vector3f normal = surface_normal(sphere_nearest, hit.p);
		Vector3f dir_random = add(normal, random_in_unit_sphere());
		Vector3f dir_reflected = sub(ray.d, mul(2.0f*dot(normal, ray.d), normal));
		Material *mat = &world->materials[sphere_nearest->material_id];
		// TO DO: Linear interpolation might not be the right thing here.
		ray = Ray{hit.p, lerp(mat->diffuse, dir_random, dir_reflected)};
		f32 iangle = 0.0f;  // TO DO: compute incident angle.
		f32 oangle = 0.0f;  // TO DO: compute outgoing angle.
		Color3f a = bounce_attenuation(mat, iangle, oangle);
		attenuation = mul(attenuation, a);

		// TO DO: early exit if attenuation is very small.
	}	
	return Color3fs::black;
}

void render(World *world, Frame *eye_frame, Color4b *img_data, f32 width, f32 height, f32 resolution, Color3f fully_saturated_color) {
	int img_width = width * resolution;
	int img_height = height * resolution;
	Point screen_p = sub(eye_frame->p, eye_frame->z);

	int px_samples = 7;
	f32 px_size = 1.0f/resolution;
	f32 space_between_samples = px_size / (f32)px_samples;

	for (int y = 0; y < img_height; ++y) {
		for (int x = 0; x < img_width; ++x) {
			Color3f px_color = {};

			Vector3f screen_vy = mul((f32)y/(f32)resolution - height/2.0f, eye_frame->y);
			for (int ysample = 0; ysample < px_samples; ++ysample) {
				Vector3f screen_vx = mul((f32)x/(f32)resolution - width/2.0f, eye_frame->x);
				for (int xsample = 0; xsample < px_samples; ++xsample) {

					Point pixel_p = add(screen_p, add(screen_vx, screen_vy));
					Color3f ray_color = trace_ray(world, ray_to_from(pixel_p, eye_frame->p));
					px_color = add(px_color, ray_color);

					screen_vx = add(screen_vx, mul(space_between_samples, eye_frame->x));
				}
				screen_vy = add(screen_vy, mul(space_between_samples, eye_frame->y));
			}

			px_color = div(px_color, (f32)(px_samples * px_samples));
			img_data[(img_height - 1 - y)*img_width + x] = color_3f_to_4b(px_color, fully_saturated_color);
		}
	}
}
