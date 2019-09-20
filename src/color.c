#ifdef INCLUDED_COLOR
#  error duplicate include: COLOR
#endif
#define INCLUDED_COLOR


struct Color4b {
	byte r, g, b, a;
};

struct Color4f {
	float r, g, b, a;
};

internal Color4f color_4b_to_4f(Color4b c) {
	return Color4f{
		(float)c.r / 255.0f,
		(float)c.g / 255.0f,
		(float)c.b / 255.0f,
		(float)c.a / 255.0f,
	};
}

internal Color4b color_4f_to_4b(Color4f c) {
	return Color4b{
		(byte)(c.r * 255.0f),
		(byte)(c.g * 255.0f),
		(byte)(c.b * 255.0f),
		(byte)(c.a * 255.0f),
	};	
}