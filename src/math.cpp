#ifdef INCLUDED_MATH
#  error duplicate include: MATH
#endif
#define INCLUDED_MATH


#include <math.h>
#include <float.h>


// Trigonometry

#ifndef M_PI
#  define M_PI 3.14159265358979323846264338327950288
#endif

namespace {
	const f32 pi = M_PI;
	const f32 tau = 2.0f * M_PI;
	const f32 max_f32 = FLT_MAX;
}

// f32

internal f32 clamp(f32 x, f32 min, f32 max) {
	return x < min ? min : (x > max ? max : x);
}

internal f32 square(f32 x) {
	return x * x;
}


// Vector3f

struct Vector3f {
	f32 x, y, z;
};

internal Vector3f add(Vector3f v, Vector3f w) {
	return Vector3f{ v.x + w.x, v.y + w.y, v.z + w.z };
}

internal Vector3f sub(Vector3f v, Vector3f w) {
	return Vector3f{ v.x - w.x, v.y - w.y, v.z - w.z };
}

internal Vector3f neg(Vector3f v) {
	return Vector3f{ -v.x, -v.y, -v.z };
}

internal Vector3f mul(f32 l, Vector3f v) {
	return Vector3f{ l * v.x, l * v.y, l * v.z };
}

internal Vector3f div(Vector3f v, f32 l) {
	return Vector3f{ v.x / l, v.y / l, v.z / l };
}

internal f32 dot(Vector3f v, Vector3f w) {
	return v.x*w.x + v.y*w.y + v.z*w.z;
}

internal f32 square(Vector3f v) {
	return dot(v, v);
}

internal f32 norm(Vector3f v) {
	return sqrt(square(v));
}

internal Vector3f normalize(Vector3f v) {
	return div(v, norm(v));
}

internal Vector3f lerp(f32 l, Vector3f v, Vector3f w) {
	return add(mul(l, v), mul(1.0f - l, w));
}


// Point

struct Point {
	f32 x, y, z;
};

internal Point add(Point p, Vector3f v) {
	return Point{ p.x + v.x, p.y + v.y, p.z + v.z };
}

internal Point sub(Point p, Vector3f v) {
	return Point{ p.x - v.x, p.y - v.y, p.z - v.z };
}

internal Vector3f sub(Point p1, Point p0) {
	return Vector3f{ p1.x - p0.x, p1.y - p0.y, p1.z - p0.z };
}


// Random

internal f32 random_f32() {
	return (f32)rand() / RAND_MAX;
}

internal Vector3f random_in_unit_cube() {
	return sub(mul(2.0f, Vector3f{random_f32(), random_f32(), random_f32()}), Vector3f{1.0f, 1.0f, 1.0f});
}

internal Vector3f random_in_unit_sphere() {
	while (1) {
		Vector3f v = random_in_unit_cube();
		if (norm(v) < 1.0f) return v; 
	}
}


// Ray

struct Ray {
	Point p;
	Vector3f d;
};

internal Ray ray_to_from(Point b, Point a) {
	return Ray{a, sub(b, a)};
}
