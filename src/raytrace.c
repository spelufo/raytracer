#ifdef INCLUDED_RAYTRACE
#  error duplicate include: RAYTRACE
#endif
#define INCLUDED_RAYTRACE


namespace {
	const float RAY_MISS = 1000.0f;
}


struct Sphere {
	Point p;
	float radius;
	Color4f color;
};

internal Vector3f surface_normal(Sphere *sphere, Point p) {
	return normalize(sub(p, sphere->p));
}

internal float intersect(Sphere *sphere, Ray ray) {
	Vector3f rayp_sphere = sub(ray.p, sphere->p);
	float a2 = square(ray.n);
	float b2 = dot(ray.n, rayp_sphere);
	float c2 = square(rayp_sphere) - square(sphere->radius);
	float arg_sqrt = square(b2) - a2 * c2;
	if (arg_sqrt < 0) return RAY_MISS;
	float t = - (b2 + sqrtf(arg_sqrt)) / a2;
	return t > 0 ? t : RAY_MISS;
}
