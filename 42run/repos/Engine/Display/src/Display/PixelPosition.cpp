#include "Display/PixelPosition.hpp"



PixelPosition::~PixelPosition()
{ }
PixelPosition::PixelPosition()
	: Corner()
	, Center()
{ }

PixelPosition::PixelPosition(const PixelPosition & other)
	: Corner(other.Corner)
	, Center(other.Center)
{ }
PixelPosition & PixelPosition::operator=(const PixelPosition & other)
{
	Corner = other.Corner;
	Center = other.Center;
	return *this;
}
