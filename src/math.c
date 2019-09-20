#ifdef INCLUDED_MATH
#  error duplicate include: MATH
#endif
#define INCLUDED_MATH


// Trigonometry

namespace {
	const float pi = M_PI;
	const float tau = 2.0f * M_PI;
}

// Float

internal float clamp(float x, float min, float max) {
	return x < min ? min : (x > max ? max : x);
}

internal float square(float x) {
	return x * x;
}


// Vector3f

struct Vector3f {
	float x, y, z;
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

internal Vector3f mul(float l, Vector3f v) {
	return Vector3f{ l * v.x, l * v.y, l * v.z };
}

internal Vector3f div(Vector3f v, float l) {
	return Vector3f{ v.x / l, v.y / l, v.z / l };
}

internal float dot(Vector3f v, Vector3f w) {
	return v.x*w.x + v.y*w.y + v.z*w.z;
}

internal float square(Vector3f v) {
	return dot(v, v);
}

internal Vector3f normalize(Vector3f v) {
	return div(v, sqrt(square(v)));
}


// Point

struct Point {
	float x, y, z;
};

internal Point add(Point p, Vector3f v) {
	return Point{ p.x + v.x, p.y + v.y, p.z + v.z };
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
