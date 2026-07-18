#ifndef  NEW_POLYHEDRA_PALLET_HPP
# define NEW_POLYHEDRA_PALLET_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Buffer/Element.hpp"
# include "Graphics/Texture/Array2D.hpp"

# include <string>

class PolyHedra;

namespace Attribute { class Layout; };

namespace NewPolyHedra
{
struct Pallet
{
	public:
	PolyHedra *		Object = nullptr;
	std::string		Name;

	public:
	~Pallet();
	Pallet();
	Pallet(const Pallet & other) = delete;
	Pallet & operator=(const Pallet & other) = delete;

	public:
	Pallet(PolyHedra * object);
	Pallet(PolyHedra * object, std::string name);



	public:
	::Buffer::Array			BufferFull;
	::Buffer::Array			BufferWire;
	::Buffer::Element		BufferWireElem;
	::Texture::Array2D		Texture;

	public:
	void	GraphicsPut();
	void	GraphicsInitFull();
	void	GraphicsInitWire();

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
};
};

#endif