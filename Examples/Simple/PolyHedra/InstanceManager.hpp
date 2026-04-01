#ifndef  POLYHEDRA_INSTANCE_MANAGER_HPP
# define POLYHEDRA_INSTANCE_MANAGER_HPP

# include "PolyHedra/Graphics/Full/Buffer.hpp"

# include "ValueType/Trans3D.hpp"
# include "Miscellaneous/Container/Binary.hpp"

class PolyHedra;
struct PolyHedraObjectData;

struct PolyHedraInstanceManager
{
	::PolyHedra *				PolyHedra;
	::PolyHedraFull::Buffer		Buffer;
	Container::Binary<Trans3D>	Instances;

	~PolyHedraInstanceManager();
	PolyHedraInstanceManager();
	PolyHedraInstanceManager(const PolyHedraInstanceManager & other);
	PolyHedraInstanceManager & operator=(const PolyHedraInstanceManager & other);

	PolyHedraInstanceManager(::PolyHedra * polyhedra);

	void	GraphicsCreate();
	void	GraphicsDelete();

	void	InitExternal();
	void	InitInternal();

	void	UpdateBufferMain();
	void	UpdateBufferInst();
	void	Draw();

	void	Clear();
	void	Place(const PolyHedraObjectData & obj);
	void	Place(const Container::Member<PolyHedraObjectData> & objs);
};

#endif