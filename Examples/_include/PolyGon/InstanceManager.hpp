#ifndef  POLYGON_INSTANCE_MANAGER_HPP
# define POLYGON_INSTANCE_MANAGER_HPP

# include "PolyGon/Graphics/Full/Buffer.hpp"
# include "PolyGon/Graphics/Wire/Buffer.hpp"

# include "Miscellaneous/Container/Binary.hpp"
# include "Instance/Basic2D/Data.hpp"

class PolyGon;
struct PolyGonObjectData;

struct PolyGonInstanceManager
{
	::PolyGon *					PolyGon;
	
	bool						UpdateFullMain;
	bool						UpdateWireMain;
	
	::PolyGonFull::Buffer		BufferFull;
	::PolyGonWire::Buffer		BufferWire;

	Container::Binary<Instance::Basic2D::Data>	InstancesFull;
	Container::Binary<Instance::Basic2D::Data>	InstancesWire;

	~PolyGonInstanceManager();
	PolyGonInstanceManager();
	PolyGonInstanceManager(const PolyGonInstanceManager & other);
	PolyGonInstanceManager & operator=(const PolyGonInstanceManager & other);

	PolyGonInstanceManager(::PolyGon * PolyGon);
	void	Change(::PolyGon * PolyGon);



	void	GraphicsCreate();
	void	GraphicsDelete();

	void	InitExternal();
	void	InitInternal();



	void	UpdateBufferFullMain();
	void	UpdateBufferFullInst();
	void	DrawFull();

	void	UpdateBufferWireMain();
	void	UpdateBufferWireInst();
	void	DrawWire();



	void	ClearInstances();
	void	PlaceInstance(const PolyGonObjectData & obj);
	void	PlaceInstances(const Container::Member<PolyGonObjectData> & objs);
};

#endif