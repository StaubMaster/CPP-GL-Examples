#include "ValueType/Color/F4.hpp"



ColorF4::~ColorF4()
{ }
ColorF4::ColorF4()
	: R(0.0f)
	, G(0.0f)
	, B(0.0f)
	, A(0.0f)
{ }

ColorF4::ColorF4(float r, float g, float b)
	: R(r)
	, G(g)
	, B(b)
	, A(1.0f)
{ }
ColorF4::ColorF4(float r, float g, float b, float a)
	: R(r)
	, G(g)
	, B(b)
	, A(a)
{ }



ColorF4 ColorF4::FromRGBA(unsigned int rgba)
{
	return ColorF4(
		((rgba >> 0x00) & 0xFF) / 255.0f,
		((rgba >> 0x08) & 0xFF) / 255.0f,
		((rgba >> 0x10) & 0xFF) / 255.0f,
		((rgba >> 0x10) & 0xFF) / 255.0f
	);
}
unsigned int ColorF4::ToRGBA() const
{
	unsigned char r = R * 255.0f;
	unsigned char g = G * 255.0f;
	unsigned char b = B * 255.0f;
	unsigned char a = A * 255.0f;
	return ((r << 0x00) | (g << 0x08) | (b << 0x10) | (a << 0x18));
}

ColorF4 ColorF4::FromRGB(unsigned int rgb)
{
	return ColorF4(
		((rgb >> 0x00) & 0xFF) / 255.0f,
		((rgb >> 0x08) & 0xFF) / 255.0f,
		((rgb >> 0x10) & 0xFF) / 255.0f
	);
}



#include "ValueType/Color/U4.hpp"
ColorU4 ColorF4::ToColorU4() const
{
	return ColorU4(
		R * 255,
		G * 255,
		B * 255,
		A * 255
	);
}
