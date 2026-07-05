#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP

# include "Miscellaneous/Container/Binary.hpp"
# include "Graphics/Buffer/VertexArray.hpp"
# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Buffer/Uniform.hpp"

struct NewPolyHedra_Pallet;
struct NewPolyHedra_ObjectData;

struct NewPolyHedra_PalletObjectManager
{
	NewPolyHedra_Pallet *	Pallet;

	NewPolyHedra_PalletObjectManager();



	virtual void	InstancesClear() = 0;
	virtual void	InstancePut(const NewPolyHedra_ObjectData & data) = 0;
	virtual void	InstancePut(const NewPolyHedra_ObjectData * data) = 0;
	virtual void	InstancesToBuffer() = 0;



	::VertexArray			BufferVertexArray;
	::Buffer::Array			Buffer;
	::Buffer::Uniform *		BufferUniform = nullptr;
	
	void	VertexBufferInit();

	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsDraw();
};

#endif