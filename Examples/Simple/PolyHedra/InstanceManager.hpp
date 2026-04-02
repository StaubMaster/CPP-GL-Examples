#ifndef  POLYHEDRA_INSTANCE_MANAGER_HPP
# define POLYHEDRA_INSTANCE_MANAGER_HPP

# include "PolyHedra/Graphics/Full/Buffer.hpp"
# include "Graphics/Texture/Array2D.hpp"

# include "Miscellaneous/Container/Binary.hpp"
# include "Instance/Basic3D/Data.hpp"

class PolyHedra;
struct PolyHedraObjectData;

struct PolyHedraInstanceManager
{
	::PolyHedra *				PolyHedra;
	bool						PolyHedraChanged;

	Texture::Array2D			Texture;

	::PolyHedraFull::Buffer		BufferFull;
	Container::Binary<Instance::Basic3D::Data>	Instances;

	~PolyHedraInstanceManager();
	PolyHedraInstanceManager();
	PolyHedraInstanceManager(const PolyHedraInstanceManager & other);
	PolyHedraInstanceManager & operator=(const PolyHedraInstanceManager & other);

	PolyHedraInstanceManager(::PolyHedra * polyhedra);
	void	Change(::PolyHedra * polyhedra);



	void	GraphicsCreate();
	void	GraphicsDelete();

	void	InitExternal();
	void	InitInternal();



	void	UpdateBufferMain();
	void	UpdateBufferInst();
	void	DrawFull();



	void	Clear();
	void	Place(const PolyHedraObjectData & obj);
	void	Place(const Container::Member<PolyHedraObjectData> & objs);
};

#endif