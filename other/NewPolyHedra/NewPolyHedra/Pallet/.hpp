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
	private:
	PolyHedra *		Object = nullptr;
	std::string		Name;

	public:
	bool	Equals(const PolyHedra * polyhedra) const;
	bool	Equals(const PolyHedra & polyhedra) const;

	public:
	bool	Equals(const std::string & name) const;
	bool	Equals(const char * name) const;

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
	private:
	void	GraphicsPutFull();
	void	GraphicsPutWire();
	public:
	void	GraphicsInitFull();
	void	GraphicsInitWire();

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
};
};

#endif