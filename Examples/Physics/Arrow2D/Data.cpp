#include "Arrow2D/Data.hpp"



Arrow2D::Data::~Data()
{ }
Arrow2D::Data::Data()
	: DataArray()
	, DisplayThisFrame(true)
	, DisposeThisFrame(false)
{ }
Arrow2D::Data::Data(unsigned int count)
	: DataArray(count)
	, DisplayThisFrame(true)
	, DisposeThisFrame(false)
{ }



void Arrow2D::Data::Dispose()
{
	DataArray.Clear();
}
void Arrow2D::Data::Allocate(unsigned int count)
{
	DataArray.Allocate(count, count);
}
