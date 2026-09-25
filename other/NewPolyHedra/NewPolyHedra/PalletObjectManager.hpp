#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_MANAGER_HPP

# include "Generics/Container/Binary.hpp"
# include "Graphics/VertexArray/Base.hpp"
# include "Graphics/Buffer/Array.hpp"
# include "Graphics/Buffer/Uniform.hpp"

namespace NewPolyHedra
{
struct Pallet;
struct ObjectData;

struct PalletObjectManager
{
	public:
	NewPolyHedra::Pallet *	Pallet = nullptr;

	public:
	virtual ~PalletObjectManager();
	PalletObjectManager();
	PalletObjectManager(const PalletObjectManager & other) = delete;
	PalletObjectManager & operator=(const PalletObjectManager & other) = delete;

	public:
	PalletObjectManager(NewPolyHedra::Pallet * pallet);



	public:
	virtual unsigned int	InstancesFullCount() const = 0;
	virtual unsigned int	InstancesWireCount() const = 0;
	public:
	virtual void	InstancesFullClear() = 0;
	virtual void	InstancesWireClear() = 0;
	public:
	virtual void	InstancesFullPut(const void * data) = 0;
	virtual void	InstancesWirePut(const void * data) = 0;
	public:
	virtual void	InstancesFullToBuffer() = 0;
	virtual void	InstancesWireToBuffer() = 0;



	public:
	::VertexArray::Base		BufferFull;
	::VertexArray::Base		BufferWire;

	::Buffer::Array		BufferFullInstance;
	::Buffer::Array		BufferWireInstance;

	unsigned int	CountFull = 0;
	unsigned int	CountWire = 0;

	void	GraphicsCreate();
	void	GraphicsDelete();

	void	GraphicsDrawFull();
	void	GraphicsDrawWire();
};
};

#endif