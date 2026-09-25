#include "Graphics/Texture/Array2D.hpp"
#include "ValueType/Vector/U3.hpp"

#include "Image.hpp"
#include "FileInfo.hpp"

#include "OpenGL.hpp"



Texture::Array2D::Array2D()
	: Texture::Base(GL::TextureTarget::Texture2DArray)
{ }
Texture::Array2D::~Array2D()
{ }

Texture::Array2D::Array2D(const Array2D & other) :
	Base(other)
{ }
Texture::Array2D & Texture::Array2D::operator=(const Array2D & other)
{
	Base::operator=(other);
	return *this;
}



void Texture::Array2D::Assign(VectorU3 size)
{
	Size = size;
	Full3D(Size, nullptr);
	DefaultParams();
}
void Texture::Array2D::Assign(unsigned int offset, const Image & img)
{
	if (img.W() == Size.X && img.H() == Size.Y)
	{
		Part3D(VectorU3(Size.X, Size.Y, 1), VectorU3(0, 0, offset), (ColorU4*)img.Data());
	}
	else
	{
		Image scaled = img.Scaled(VectorU2(Size.X, Size.Y));
		Assign(offset, scaled);
	}
}
void Texture::Array2D::Assign(unsigned int offset, const FileInfo & file)
{
	Image img = file.LoadImage();
	Assign(offset, img);
	img.Dispose();
}



void Texture::Array2D::Assign(const Image & img)
{
	Size = VectorU3(img.W(), img.H(), 1);
	Full3D(Size, (ColorU4*)img.Data());
	DefaultParams();
}
void Texture::Array2D::Assign(const FileInfo & file)
{
	Image img = file.LoadImage();
	Assign(img);
	img.Dispose();
}



void Texture::Array2D::Assign(VectorU2 size, const Container::Array<Image> & imgs)
{
	Assign(VectorU3(size.X, size.Y, imgs.Length()));
	Image missing = Image::Missing(VectorU2(4, 4));
	missing.Scale(size);
	for (unsigned int i = 0; i < imgs.Length(); i++)
	{
		if (imgs[i].Empty())
		{
			Assign(i, missing);
		}
		else
		{
			Assign(i, imgs[i]);
		}
	}
	missing.Dispose();
}
void Texture::Array2D::Assign(VectorU2 size, const Container::Array<FileInfo> & files)
{
	Assign(VectorU3(size.X, size.Y, files.Length()));

	Image missing = Image::Missing(VectorU2(4, 4));
	missing.Scale(size);

	for (unsigned int i = 0; i < files.Length(); i++)
	{
		Image img = files[i].LoadImage();
		if (img.Empty())
		{
			Assign(i, missing);
		}
		else
		{
			Assign(i, img);
		}
	}
}
