#include "PolyHedra/Skin/Skin.hpp"
#include "PolyHedra/Skin/Data.hpp"
#include "Graphics/Texture/Array2D.hpp"
#include "Image.hpp"

#include "FileInfo.hpp"

#include "ValueType/Vector/F2.hpp"

#include <iostream>
#include "ValueType/_Show.hpp"



Skin::Skin()
	: Size()
	, Color(1.0f, 1.0f, 1.0f, 1.0f)
	, Images()
	, Faces()
	, File()
	, Name()
{ }
Skin::~Skin()
{ }



void Skin::Done()
{
	Faces.Trim();
}
Texture::Array2D Skin::ToTexture() const
{
	Texture::Array2D tex;
	tex.Create();
	tex.Assign(Size, Images.ToArray());
	return tex;
}



void Skin::Insert_Face3(unsigned int idx0, unsigned int idx1, unsigned int idx2)
{
	Faces.Insert(Face(idx0, idx1, idx2));
}
void Skin::Insert_Face4(unsigned int idx0, unsigned int idx1, unsigned int idx2, unsigned int idx3)
{
	Faces.Insert(Face(idx0, idx1, idx2));
	Faces.Insert(Face(idx2, idx1, idx3));
}
