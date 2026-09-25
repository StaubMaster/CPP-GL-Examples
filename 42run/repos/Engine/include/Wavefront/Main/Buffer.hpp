#ifndef  WAVEFRONT_OBJ_MAIN_BUFFER_HPP
# define WAVEFRONT_OBJ_MAIN_BUFFER_HPP

# include "Graphics/Buffer/Array.hpp"

# include "Graphics/Attribute/VectorF4.hpp"
# include "Graphics/Attribute/VectorF3.hpp"
# include "Graphics/Attribute/ColorF4.hpp"
# include "Graphics/Attribute/General/Float1.hpp"

namespace BufferArray { class Base; };

namespace Wavefront
{
namespace Main
{
class Buffer : public ::Buffer::Array
{
	public:
	::Attribute::VectorF4	Position;
	::Attribute::VectorF3	Texture;
	::Attribute::VectorF3	Normal;
	::Attribute::ColorF4	Color;

	::Attribute::ColorF4	AmbientColor;
	::Attribute::ColorF4	DiffuseColor;
	::Attribute::Float1		SpecularPower;
	::Attribute::ColorF4	SpecularColor;

	public:
	~Buffer();
	Buffer(VertexArray & vertex_array);

	Buffer(const Buffer & other) = delete;
	Buffer & operator=(const Buffer & other) = delete;
};
};
};

#endif