#ifndef  NEW_POLYHEDRA_BASE_LOGICAL_DATA_HPP
# define NEW_POLYHEDRA_BASE_LOGICAL_DATA_HPP

namespace NewPolyHedra
{
struct BaseDisplayData;
struct BaseLogicalData
{
	public:
	bool	Remove = false;
	// make this private
	// make function that sets

	private:
	bool	DisplayFull = true;
	public:
	void	ShowFull();
	void	HideFull();
	bool	VisibleFull() const;

	private:
	bool	DisplayWire = false;
	public:
	void	ShowWire();
	void	HideWire();
	bool	VisibleWire() const;

	public:
	BaseDisplayData *	Graphics = nullptr;

	public:
	virtual ~BaseLogicalData() = default;
	BaseLogicalData() = default;
	BaseLogicalData(const BaseLogicalData & other) = default;
	BaseLogicalData & operator=(const BaseLogicalData & other) = default;

	public:
	BaseLogicalData(BaseDisplayData * graphics);

	protected:
	virtual const void *	DataVoid() const = 0;

	public:
	void	InstancePut() const;
};
};

#endif