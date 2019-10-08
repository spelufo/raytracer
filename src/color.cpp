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

// Convert a Color3f to an aprox. sRGB Color4b.
internal Color4b color_3f_to_4b(Color3f c, Color3f max) {
	return Color4b{
		(u8)(sqrt(c.r/max.r) * 255.0f),
		(u8)(sqrt(c.g/max.g) * 255.0f),
		(u8)(sqrt(c.b/max.b) * 255.0f),
		255,
	};	
}
