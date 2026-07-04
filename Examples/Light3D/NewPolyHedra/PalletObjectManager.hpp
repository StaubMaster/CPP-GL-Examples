#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Graphics/Buffer/VertexArray.hpp"
# include "Graphics/Buffer/Array.hpp"

struct NewPolyHedra_Pallet;
struct NewPolyHedra_ObjectData;

struct NewPolyHedra_PalletObjectManager
{
	NewPolyHedra_Pallet *	Pallet;
	::VertexArray			BufferVertexArray;
	::Buffer::Array			Buffer;

	NewPolyHedra_PalletObjectManager();

	virtual void	InstancesClear() = 0;
	virtual void	InstancePut(const NewPolyHedra_ObjectData & data) = 0;
	virtual void	InstancePut(const NewPolyHedra_ObjectData * data) = 0;
	virtual void	InstancesToBuffer() = 0;

	void	VertexBufferInit();

	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsDraw();
};

#endif