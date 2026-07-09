#ifndef  NEW_POLYHEDRA_PALLET_HPP
# define NEW_POLYHEDRA_PALLET_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Buffer/Element.hpp"
# include "Graphics/Texture/Array2D.hpp"

# include <string>

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet
{
	public:
	PolyHedra *		Object;
	void	Put();

	public:
	std::string		Name;

	public:
	~Pallet();
	Pallet(PolyHedra * object);
	Pallet(const Pallet & other) = delete;
	Pallet & operator=(const Pallet & other) = delete;



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
};

#endif