#ifndef  NEW_POLYHEDRA_PALLET_HPP
# define NEW_POLYHEDRA_PALLET_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Buffer/Element.hpp"
# include "Graphics/Texture/Array2D.hpp"

class PolyHedra;

struct NewPolyHedra_Pallet
{
	public:
	PolyHedra *		Object;
	void	Put();



	public:
	~NewPolyHedra_Pallet();
	NewPolyHedra_Pallet(PolyHedra * object);



	public:
	::Buffer::Array			BufferFull;
	::Buffer::Array			BufferWire;
	::Buffer::Element		BufferWireElem;
	::Attribute::Layout *	BufferFullLayout;
	::Attribute::Layout *	BufferWireLayout;
	::Texture::Array2D		Texture;

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
};

#endif