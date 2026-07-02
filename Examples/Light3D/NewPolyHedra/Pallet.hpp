#ifndef  NEW_POLYHEDRA_PALLET_HPP
# define NEW_POLYHEDRA_PALLET_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Texture/Array2D.hpp"

class PolyHedra;

struct NewPolyHedra_Pallet
{
	PolyHedra *		Object;
	::Buffer::Array		Buffer;
	::Texture::Array2D		Texture;

	NewPolyHedra_Pallet();

	void	GraphicsCreate();
	void	GraphicsDelete();
};

#endif