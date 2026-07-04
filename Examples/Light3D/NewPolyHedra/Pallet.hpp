#ifndef  NEW_POLYHEDRA_PALLET_HPP
# define NEW_POLYHEDRA_PALLET_HPP

# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Texture/Array2D.hpp"

class PolyHedra;

struct NewPolyHedra_Pallet
{
	private:
	PolyHedra *		Object;

	public:
	::Buffer::Array			Buffer;
	::Texture::Array2D		Texture;
	::Attribute::Layout * 	Layout;

	public:
	bool	Is(PolyHedra * object) const;

	public:
	~NewPolyHedra_Pallet();
	NewPolyHedra_Pallet(PolyHedra * object);

	public:
	void	Put();

	public:
	void	GraphicsCreate();
	void	GraphicsDelete();
};

#endif