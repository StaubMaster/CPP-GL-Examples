#ifndef  WAVEFRONT_OBJ_MAIN_DATA_HPP
# define WAVEFRONT_OBJ_MAIN_DATA_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/Vector/F4.hpp"
# include "ValueType/Color/U4.hpp"

namespace Wavefront
{
namespace Main
{
struct Data
{
	VectorF4	Position;
	VectorF3	Texture;
	VectorF3	Normal;
	ColorF4	Color;

	ColorF4	AmbientColor;
	ColorF4	DiffuseColor;
	float	SpecularPower;
	ColorF4	SpecularColor;
};
};
};

#endif