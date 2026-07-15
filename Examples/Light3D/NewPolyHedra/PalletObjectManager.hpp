#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP

# include "Generics/Container/Binary.hpp"
# include "Graphics/VertexArray/MainInstEx.hpp"
# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Buffer/Uniform.hpp"

namespace NewPolyHedra
{
struct Pallet;
struct ObjectData;

struct PalletObjectManager
{
	public:
	NewPolyHedra::Pallet *	Pallet;

	public:
	~PalletObjectManager();
	PalletObjectManager();
	PalletObjectManager(const PalletObjectManager & other) = delete;
	PalletObjectManager & operator=(const PalletObjectManager & other) = delete;

	public:
	PalletObjectManager(NewPolyHedra::Pallet * pallet);



	public:
	virtual void	InstancesClear() = 0;
	virtual void	InstancePutFull(const void * data) = 0;
	virtual void	InstancePutWire(const void * data) = 0;
	virtual void	InstancesToBufferFull() = 0;
	virtual void	InstancesToBufferWire() = 0;



	public:
	::VertexArray::MainInstEx	BufferFullVertexArray;
	::VertexArray::MainInstEx	BufferWireVertexArray;
	::Buffer::Array				BufferFull;
	::Buffer::Array				BufferWire;
	::Buffer::Uniform *			BufferUniform = nullptr;

	public:
	void	VertexBufferInit();

	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsDrawFull();
	void	GraphicsDrawWire();
};
};

#endif