#include "Graphics/Texture/Base.hpp"
#include "ValueType/Vector/U3.hpp"
#include "OpenGL.hpp"
#include <sstream>

#include "Debug.hpp"
#include "ValueType/_Show.hpp"
#include <iostream>

GL::TextureID Texture::Base::None = 0;

void Texture::Base::LogInfo(bool self) const
{
	if (self)
	{
		Debug::Log << Debug::Tabs << "Texture Info\n";
		Debug::Log << Debug::TabInc;
	}
	Debug::Log << Debug::Tabs << "ID " << ID << '\n';
	Debug::Log << Debug::Tabs << "Target " << Target << '\n';
	if (self)
	{
		Debug::Log << Debug::TabDec;
		Debug::Log << Debug::Done;
	}
}



Texture::Base::Base(GL::TextureTarget target) :
	Target(target),
	ID(None)
{ }
Texture::Base::~Base()
{ }

Texture::Base::Base(const Base & other) :
	Target(other.Target),
	ID(other.ID)
{ }
Texture::Base & Texture::Base::operator=(const Base & other)
{
	ID = other.ID;
	Target = other.Target;
	return *this;
}



bool Texture::Base::Exists() const { return (ID != None); }
bool Texture::Base::IsBound() const { return (Bound(Target) == ID); }
void Texture::Base::Bind()
{
	if (Exists() && !IsBound())
	{
		GL::BindTexture(Target, ID);
	}
}

GL::TextureID Texture::Base::Bound(GL::TextureTarget target)
{
	GL::ParameterName name;
	switch (target)
	{
		case GL::TextureTarget::Texture2DArray: name = GL::ParameterName::TextureBinding2DArray; break;
		default: return None;
	};
	int ID;
	GL::GetIntegerv(name, ID);
	return ID;
}
void Texture::Base::BindNone(GL::TextureTarget target)
{
	GL::BindTexture(target, None);
}



void Texture::Base::Create()
{
	if (ID != None) { return; }

	Debug::Log << "Texture::Base Creating " << ID << " ..." << Debug::Done;
	ID = GL::CreateTexture();
	Debug::Log << "Texture::Base Creating " << ID << " done" << Debug::Done;
}
void Texture::Base::Delete()
{
	if (ID == None) { return; }

	Debug::Log << "Texture::Base Deleting " << ID << " ..." << Debug::Done;
	GL::DeleteTexture(ID);
	ID = 0;
	Debug::Log << "Texture::Base Deleting " << ID << " done" << Debug::Done;
}



/*
GL_DEPTH_STENCIL_TEXTURE_MODE

GL_TEXTURE_BASE_LEVEL

GL_TEXTURE_COMPARE_FUNC
GL_TEXTURE_COMPARE_MODE

GL_TEXTURE_MIN_FILTER
	GL_NEAREST
	GL_LINEAR
	GL_NEAREST_MIPMAP_NEAREST
	GL_LINEAR_MIPMAP_NEAREST
	GL_NEAREST_MIPMAP_LINEAR
	GL_LINEAR_MIPMAP_LINEAR
GL_TEXTURE_MAG_FILTER
	GL_NEAREST
	GL_LINEAR

GL_TEXTURE_LOD_BIAS		LOD Offset ?
GL_TEXTURE_MIN_LOD
GL_TEXTURE_MAX_LOD
GL_TEXTURE_MAX_LEVEL

GL_TEXTURE_SWIZZLE_R
GL_TEXTURE_SWIZZLE_G
GL_TEXTURE_SWIZZLE_B
GL_TEXTURE_SWIZZLE_A
GL_TEXTURE_SWIZZLE_RGBA
	GL_RED		= col.r
	GL_GREEN	= col.g
	GL_BLUE		= col.b
	GL_ALPHA	= col.a
	GL_ZERO		= 0.0
	GL_ONE		= 1.0

GL_TEXTURE_WRAP_S	X
GL_TEXTURE_WRAP_T	Y
GL_TEXTURE_WRAP_R	Z
	GL_REPEAT				= Modular Loop
	GL_MIRRORED_REPEAT		= Modular Loop Reverse
	GL_CLAMP_TO_EDGE		= Edge
	GL_MIRROR_CLAMP_TO_EDGE	= 
	GL_CLAMP_TO_BORDER		= GL_TEXTURE_BORDER_COLOR
*/
void Texture::Base::DefaultParams()
{
	WrapX(WrapType::Repeat);
	WrapY(WrapType::Repeat);
	FilterMin(FilterMinType::Nearest);
	FilterMag(FilterMagType::Nearest);
	glGenerateMipmap((unsigned int)Target);
}
void Texture::Base::WrapX(WrapType wrap)
{
	GL::TexParameteri(Target, GL::TextureParameterName::TextureWrapS, (int)wrap);
}
void Texture::Base::WrapY(WrapType wrap)
{
	GL::TexParameteri(Target, GL::TextureParameterName::TextureWrapT, (int)wrap);
}
void Texture::Base::WrapZ(WrapType wrap)
{
	GL::TexParameteri(Target, GL::TextureParameterName::TextureWrapR, (int)wrap);
}
void Texture::Base::FilterMin(FilterMinType filter)
{
	GL::TexParameteri(Target, GL::TextureParameterName::TextureMinFilter, (int)filter);
}
void Texture::Base::FilterMag(FilterMagType filter)
{
	GL::TexParameteri(Target, GL::TextureParameterName::TextureMagFilter, (int)filter);
}





void Texture::Base::Full3D(VectorU3 size, const ColorU4 * data)
{
	Bind();
	GL::TexImage3D(Target, 0, GL::InternalFormat::Rgba8, size.X, size.Y, size.Z, 0, GL::PixelDataFormat::Rgba, GL::PixelDataType::UnsignedInt8888Rev, data);
}
void Texture::Base::Part3D(VectorU3 size, VectorU3 offset, const ColorU4 * data)
{
	Bind();
	GL::TexSubImage3D(Target, 0, offset.X, offset.Y, offset.Z, size.X, size.Y, size.Z, GL::PixelDataFormat::Rgba, GL::PixelDataType::UnsignedInt8888Rev, data);
}
