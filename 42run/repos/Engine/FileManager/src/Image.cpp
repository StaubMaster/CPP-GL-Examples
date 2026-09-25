#include "Image.hpp"



bool			Image::Empty() const { return Pixels.IsNull(); }
uint32			Image::W() const { return Pixels.Size().X; }
uint32			Image::H() const { return Pixels.Size().Y; }
VectorU2		Image::Size() const { return Pixels.Size(); }
const void *	Image::Data() const { return Pixels.Data(); }
void *			Image::Data() { return Pixels.Data(); }
LoopU2			Image::Loop() const { return LoopU2(VectorU2(), Pixels.Size()); }

ColorU4 & Image::Pixel(VectorU2 udx)
{
//	return Pixels[udx.X + udx.Y * Pixels.LengthX()];
	return Pixels[udx];
}
const ColorU4 & Image::Pixel(VectorU2 udx) const
{
//	return Pixels[udx.X + udx.Y * Pixels.LengthX()];
	return Pixels[udx];
}
ColorU4 & Image::Pixel(uint32 x, uint32 y)
{
//	return Pixels[x + y * Pixels.LengthX()];
	return Pixels[VectorU2(x, y)];
}
const ColorU4 & Image::Pixel(uint32 x, uint32 y) const
{
//	return Pixels[x + y * Pixels.LengthX()];
	return Pixels[VectorU2(x, y)];
}
uint8 & Image::Pixel(uint32 x, uint32 y, uint8 col)
{
//	uint8 * data = (uint8*)&Pixels[x + y * Pixels.LengthX()];
	uint8 * data = (uint8*)&Pixels[VectorU2(x, y)];
	return data[col];
}
const uint8 & Image::Pixel(uint32 x, uint32 y, uint8 col) const
{
//	const uint8 * data = (const uint8*)&Pixels[x + y * Pixels.LengthX()];
	const uint8 * data = (const uint8*)&Pixels[VectorU2(x, y)];
	return data[col];
}
ColorU4 & Image::Pixel(uint32 udx)
{
	return Pixels[udx];
}
const ColorU4 & Image::Pixel(uint32 udx) const
{
	return Pixels[udx];
}



Image::~Image() { }
Image::Image()
	: Pixels()
{ }
Image::Image(VectorU2 size)
	: Pixels(size)
{ }
Image::Image(uint32 w, uint32 h)
	: Pixels(VectorU2(w, h))
{ }

Image::Image(const Image & other)
	: Pixels(other.Pixels)
{ }
Image & Image::operator=(const Image & other)
{
	Pixels = other.Pixels;
	return *this;
}



void Image::Init(VectorU2 size)
{
	Pixels.Size(size);
}
void Image::Init(uint32 w, uint32 h)
{
	Pixels.Size(VectorU2(w, h));
}
void Image::Dispose()
{
	Pixels.Clear();
}



void Image::Scale(VectorU2 size)
{
	Pixels.Bind(Scaled(size).Pixels);
}
Image Image::Scaled(VectorU2 size) const
{
	Image img(size);

	VectorU2 scaled;
	for (uint32 y = 0; y < size.Y; y++)
	{
		scaled.Y = (((float)y) / ((float)size.Y)) * ((float)Pixels.Size().Y);
		for (uint32 x = 0; x < size.X; x++)
		{
			scaled.X = (((float)x) / ((float)size.X)) * ((float)Pixels.Size().X);
			img.Pixels[VectorU2(x, y)] = Pixels[scaled];
		}
	}

	return img;
}



Image Image::Missing(VectorU2 size)
{
	Image img(size);

	for (uint32 y = 0; y < size.Y; y++)
	{
		for (uint32 x = 0; x < size.X; x++)
		{
			ColorU4 col;
			if ((x & 1) == (y & 1))
				col = ColorU4(0x00, 0x00, 0x00);
			else
				col = ColorU4(0xFF, 0x00, 0xFF);
			img.Pixel(x, y) = col;
			//uint32 pxl;
			//if ((x & 1) == (y & 1))
			//	pxl = 0x000000FF;
			//else
			//	pxl = 0xFF00FFFF;
			//img -> Pixel(x, y) = pxl;
			//img -> setPixelRGBA(x, y, pxl);
		}
	}

	return img;
}
