#include "DisplayScale.hpp"
#include "DataStruct/Point2D.hpp"



float Normal0ToPixel(float val, float size)
{
	//	Normal [ 0 ; 1 ]
	//	Pixel [ 0 ; n ]
	return val * size;
}
float PixelToNormal0(float val, float size)
{
	//	Pixel [ 0 ; n ]
	//	Normal [ 0 ; 1 ]
	return val / size;
}
float Normal0ToNormal1(float val)
{
	//	Normal0 [ 0 ; 1 ]
	//	Normal1 [ -1 ; +1 ]
	return (val * 2) - 1;
}
float Normal1ToNormal0(float val)
{
	//	Normal1 [ -1 ; +1 ]
	//	Normal0 [ 0 ; 1 ]
	return (val + 1) / 2;
}



Point2D Normal0ToPixel(Point2D p, Point2D size)
{
	p.X = Normal0ToPixel(p.X, size.X);
	p.Y = Normal0ToPixel(p.Y, size.Y);
	return p;
}
Point2D PixelToNormal0(Point2D p, Point2D size)
{
	p.X = PixelToNormal0(p.X, size.X);
	p.Y = PixelToNormal0(p.Y, size.Y);
	return p;
}
Point2D Normal0ToNormal1(Point2D p)
{
	p.X = Normal0ToNormal1(p.X);
	p.Y = Normal0ToNormal1(p.Y);
	return p;
}
Point2D Normal1ToNormal0(Point2D p)
{
	p.X = Normal1ToNormal0(p.X);
	p.Y = Normal1ToNormal0(p.Y);
	return p;
}


