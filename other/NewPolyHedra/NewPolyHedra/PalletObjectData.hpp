#ifndef  NEW_POLYHEDRA_PALLET_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_PALLET_OBJECT_DATA_HPP


namespace NewPolyHedra
{
struct PalletObjectManager;

// rename to just "PalletObject"
struct PalletObjectData
{
	public:
	bool	Remove = false;

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
	PalletObjectManager *	Manager = nullptr;

	public:
	virtual ~PalletObjectData() = default;
	PalletObjectData() = default;
	PalletObjectData(const PalletObjectData & other) = default;
	PalletObjectData & operator=(const PalletObjectData & other) = default;

	public:
	PalletObjectData(PalletObjectManager * manager);

	protected:
	virtual const void *	DataVoid() const = 0;

	public:
	void	InstancePut() const;
};
};

#endif