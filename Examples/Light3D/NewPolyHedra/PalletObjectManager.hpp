#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP

# include "Generics/Container/Binary.hpp"
# include "Graphics/Buffer/VertexArray.hpp"
# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Buffer/Uniform.hpp"

struct NewPolyHedra_Pallet;
struct NewPolyHedra_ObjectData;

struct NewPolyHedra_PalletObjectManager
{
	public:
	NewPolyHedra_Pallet *	Pallet;

	public:
	NewPolyHedra_PalletObjectManager();



	public:
	virtual void	InstancesClear() = 0;
	virtual void	InstancePutFull(const void * data) = 0;
	virtual void	InstancePutWire(const void * data) = 0;
	virtual void	InstancesToBufferFull() = 0;
	virtual void	InstancesToBufferWire() = 0;



	public:
	::VertexArray			BufferFullVertexArray;
	::VertexArray			BufferWireVertexArray;
	::Buffer::Array			BufferFull;
	::Buffer::Array			BufferWire;
	::Buffer::Uniform *		BufferUniform = nullptr;

	public:
	void	VertexBufferInit();

	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsDrawFull();
	void	GraphicsDrawWire();
};

#endif