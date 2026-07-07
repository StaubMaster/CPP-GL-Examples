#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_DATA_HPP

struct NewPolyHedra_PalletObjectManager;

// rename to just "PalletObject"
struct NewPolyHedra_PalletObjectData
{
	public:
	bool	Remove;

	private:
	bool	DisplayFull;
	public:
	void	ShowFull();
	void	HideFull();
	bool	VisibleFull() const;

	private:
	bool	DisplayWire;
	public:
	void	ShowWire();
	void	HideWire();
	bool	VisibleWire() const;

	public:
	NewPolyHedra_PalletObjectManager *	Manager;

	public:
	virtual ~NewPolyHedra_PalletObjectData();
	NewPolyHedra_PalletObjectData();

	protected:
	virtual const void *	DataVoid() const = 0;

	public:
	void	InstancePut() const;
};

#endif