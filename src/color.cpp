#ifdef INCLUDED_COLOR
#  error duplicate include: COLOR
#endif
#define INCLUDED_COLOR


struct Color4b {
	u8 r, g, b, a;
};

struct Color3f {
	f32 r, g, b;
};

namespace Color3fs {
    const Color3f black = Color3f{0.0f, 0.0f, 0.0f};
    const Color3f white = Color3f{1.0f, 1.0f, 1.0f};
}

internal Color3f add(Color3f v, Color3f w) {
    return Color3f{ v.r + w.r, v.g + w.g, v.b + w.b };
}

internal Color3f sub(Color3f v, Color3f w) {
    return Color3f{ v.r - w.r, v.g - w.g, v.b - w.b };
}

internal Color3f neg(Color3f v) {
    return Color3f{ -v.r, -v.g, -v.b };
}

internal Color3f mul(f32 l, Color3f v) {
    return Color3f{ l * v.r, l * v.g, l * v.b };
}

internal Color3f mul(Color3f v, Color3f w) {
    return Color3f{ v.r * w.r, v.g * w.g, v.b * w.b };
}

internal Color3f div(Color3f v, f32 l) {
    return Color3f{ v.r / l, v.g / l, v.b / l };
}

internal f32 dot(Color3f v, Color3f w) {
    return v.r*w.r + v.g*w.g + v.b*w.b;
}

internal f32 square(Color3f v) {
    return dot(v, v);
}

internal Color3f normalize(Color3f v) {
    return div(v, sqrt(square(v)));
}

// Convert a Color3f to an aprox. sRGB Color4b.
internal Color4b color_3f_to_4b(Color3f c, Color3f max) {
	return Color4b{
		(u8)(sqrt(c.r/max.r) * 255.0f),
		(u8)(sqrt(c.g/max.g) * 255.0f),
		(u8)(sqrt(c.b/max.b) * 255.0f),
		255,
	};	
}
