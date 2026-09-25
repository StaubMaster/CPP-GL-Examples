#include "ValueType/Color/U4.hpp"



ColorU4::~ColorU4()
{ }
ColorU4::ColorU4()
	: R(0)
	, G(0)
	, B(0)
	, A(0)
{ }

ColorU4::ColorU4(unsigned char r, unsigned char g, unsigned char b)
	: R(r)
	, G(g)
	, B(b)
	, A(0xFF)
{ }
ColorU4::ColorU4(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	: R(r)
	, G(g)
	, B(b)
	, A(a)
{ }



ColorU4 ColorU4::FromRGBA(unsigned int rgba)
{
	return ColorU4(
		(rgba >> 0x00) & 0xFF,
		(rgba >> 0x08) & 0xFF,
		(rgba >> 0x10) & 0xFF,
		(rgba >> 0x18) & 0xFF
	);
}
unsigned int ColorU4::ToRGBA() const
{
	unsigned int rgba = 0;
	rgba |= R << 0x00;
	rgba |= G << 0x08;
	rgba |= B << 0x10;
	rgba |= A << 0x18;
	return rgba;
}

ColorU4 ColorU4::FromRGB(unsigned int rgb)
{
	return ColorU4(
		(rgb >> 0x00) & 0xFF,
		(rgb >> 0x08) & 0xFF,
		(rgb >> 0x10) & 0xFF
	);
}



#include "ValueType/Color/F4.hpp"
//ColorU4(const ColorF4 & other);
//ColorU4 & operator=(const ColorF4 & other);
ColorF4 ColorU4::ToColorF4() const
{
	return ColorF4(
		R / 255.0f,
		G / 255.0f,
		B / 255.0f,
		A / 255.0f
	);
}
