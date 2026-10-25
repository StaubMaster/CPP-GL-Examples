#ifndef  NEW_POLYHEDRA_BASE_DISPLAY_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_BASE_DISPLAY_OBJECT_MANAGER_HPP

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Attribute/General/Layout.hpp"

# include "NewPolyHedra/Pallet/Full/Layout.hpp"
# include "NewPolyHedra/Pallet/Wire/Layout.hpp"

namespace NewPolyHedra
{
struct Pallet;

struct BaseDisplayObject;
struct BaseDisplayObjectManager
{
	public:
	virtual ~BaseDisplayObjectManager() = default;
	BaseDisplayObjectManager() = default;
	BaseDisplayObjectManager(const BaseDisplayObjectManager & other) = delete;
	BaseDisplayObjectManager & operator=(const BaseDisplayObjectManager & other) = delete;

	public:		virtual unsigned int	Count() const = 0;

	public:		virtual BaseDisplayObject *		Find(const Pallet & pallet) const = 0;
	private:	virtual BaseDisplayObject &		Make(      Pallet & pallet) = 0;
	public:		virtual BaseDisplayObject &		Take(      Pallet & pallet) = 0;

//	public:		virtual BaseDisplayObject *		Find(const Pallet * pallet) const = 0;
//	private:	virtual BaseDisplayObject *		Make(      Pallet * pallet) = 0;
//	public:		virtual BaseDisplayObject *		Take(      Pallet * pallet) = 0;

	public:
	::Shader::Base	ShaderFull;
	::Shader::Base	ShaderWire;

	PalletFull::Layout		BufferFullMainLayout;
	PalletWire::Layout		BufferWireMainLayout;

	::Attribute::Layout *	BufferFullInstLayout = nullptr;
	::Attribute::Layout *	BufferWireInstLayout = nullptr;

	public:
	virtual unsigned int	InstancesFullCount() const = 0;
	virtual unsigned int	InstancesWireCount() const = 0;
	virtual void			InstancesClear() = 0;

	public:
	virtual void	GraphicsCreate() = 0;
	virtual void	GraphicsDelete() = 0;
	virtual void	GraphicsDrawFull() = 0;
	virtual void	GraphicsDrawWire() = 0;
};
};

#endif