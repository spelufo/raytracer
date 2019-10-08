#ifdef INCLUDED_MATH
#  error duplicate include: MATH
#endif
#define INCLUDED_MATH


#include <math.h>
#include <float.h>


// Trigonometry

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

internal Vector3f normalize(Vector3f v) {
	return div(v, sqrt(square(v)));
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


// Ray

struct Ray {
	Point p;
	Vector3f n;
};

internal Ray ray_to_from(Point b, Point a) {
	return Ray{a, sub(b, a)};
}
