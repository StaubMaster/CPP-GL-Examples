#ifndef  NEW_POLYHEDRA_BASE_DISPLAY_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_BASE_DISPLAY_OBJECT_MANAGER_HPP

# include "Generics/Container/Binary.hpp"

#include "NewPolyHedra/Pallet/Full/Layout.hpp"
#include "NewPolyHedra/Pallet/Wire/Layout.hpp"

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Attribute/General/Layout.hpp"

namespace NewPolyHedra
{
struct Pallet;

struct BaseDisplayObject;
struct BaseDisplayObjectManager
{
	public:
	virtual ~BaseDisplayObjectManager();
	BaseDisplayObjectManager() = default;
	BaseDisplayObjectManager(const BaseDisplayObjectManager & other) = delete;
	BaseDisplayObjectManager & operator=(const BaseDisplayObjectManager & other) = delete;

	protected:
	Container::Binary<BaseDisplayObject*>	Objects;
	public:
	unsigned int	Count() const;

	private:
	virtual	BaseDisplayObject *		NewBase(Pallet & pallet) = 0;

	public:		BaseDisplayObject *		Find(const Pallet & pallet) const;
	private:	BaseDisplayObject &		Make(      Pallet & pallet);
	public:		BaseDisplayObject &		Take(      Pallet & pallet);

	public:		BaseDisplayObject *		Find(const Pallet * pallet) const;
	private:	BaseDisplayObject *		Make(      Pallet * pallet);
	public:		BaseDisplayObject *		Take(      Pallet * pallet);

	public:
	::Shader::Base	ShaderFull;
	::Shader::Base	ShaderWire;

	PalletFull::Layout		BufferFullMainLayout;
	PalletWire::Layout		BufferWireMainLayout;

	::Attribute::Layout *	BufferFullInstLayout = nullptr;
	::Attribute::Layout *	BufferWireInstLayout = nullptr;

	public:
	unsigned int	InstancesFullCount() const;
	unsigned int	InstancesWireCount() const;

	void	InstancesClear();
	//void	InstancesMake();

	void	GraphicsCreate();
	void	GraphicsDelete();
	void	GraphicsDrawFull();
	void	GraphicsDrawWire();
};
};

#endif