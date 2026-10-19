#ifndef  NEW_POLYHEDRA_BASE_DISPLAY_OBJECT_HPP
# define NEW_POLYHEDRA_BASE_DISPLAY_OBJECT_HPP

# include "Generics/Container/Binary.hpp"

# include "Graphics/VertexArray/Base.hpp"
# include "Graphics/Buffer/Array.hpp"

namespace NewPolyHedra
{
struct Pallet;
struct ObjectData;

struct BaseDisplayObject
{
	private: public: // get Pallet, get PolyHedra
	Pallet &	PalletObject;

	public:
	bool	Equals(const Pallet & pallet) const;
	bool	Equals(const Pallet * pallet) const;

	public:
	virtual ~BaseDisplayObject() = default;
	BaseDisplayObject() = delete;
	BaseDisplayObject(const BaseDisplayObject & other) = delete;
	BaseDisplayObject & operator=(const BaseDisplayObject & other) = delete;

	public:
	BaseDisplayObject(Pallet & pallet);

	public:
	virtual unsigned int	InstancesFullCount() const = 0;
	virtual unsigned int	InstancesWireCount() const = 0;
	public:
	virtual void	InstancesFullClear() = 0;
	virtual void	InstancesWireClear() = 0;
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

	void	GraphicsInitFull(::Attribute::Layout & layout_main, ::Attribute::Layout * layout_inst);
	void	GraphicsInitWire(::Attribute::Layout & layout_main, ::Attribute::Layout * layout_inst);

	void	GraphicsDrawFull();
	void	GraphicsDrawWire();
};
};

#endif