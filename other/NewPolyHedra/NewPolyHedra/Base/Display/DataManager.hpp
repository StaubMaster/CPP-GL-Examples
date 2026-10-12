#ifndef  NEW_POLYHEDRA_BASE_DISPLAY_DATA_MANAGER_HPP
# define NEW_POLYHEDRA_BASE_DISPLAY_DATA_MANAGER_HPP

# include "Generics/Container/Binary.hpp"

# include "Graphics/Shader/Base.hpp"
# include "Graphics/Attribute/General/Layout.hpp"

namespace NewPolyHedra
{
struct Pallet;

struct BaseDisplayData;
struct BaseDisplayDataManager
{
	public:
	virtual ~BaseDisplayDataManager();
	BaseDisplayDataManager() = default;
	BaseDisplayDataManager(const BaseDisplayDataManager & other) = delete;
	BaseDisplayDataManager & operator=(const BaseDisplayDataManager & other) = delete;

	protected:
	Container::Binary<BaseDisplayData*>		s;
	public:
	unsigned int	Count() const;

	private:
	virtual	BaseDisplayData *	NewBase(Pallet & pallet) = 0;

	public:
	BaseDisplayData *	Find(Pallet * pallet) const;
	private:
	BaseDisplayData *	Make(Pallet * pallet);
	public:
	BaseDisplayData *	Take(Pallet * pallet);

	public:
	::Shader::Base	ShaderFull;
	::Shader::Base	ShaderWire;

	::Attribute::Layout *	BufferFullLayout = nullptr;
	::Attribute::Layout *	BufferWireLayout = nullptr;

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