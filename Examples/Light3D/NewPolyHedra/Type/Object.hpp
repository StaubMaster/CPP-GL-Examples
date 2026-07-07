#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_HPP

struct NewPolyHedra_Pallet;
class PolyHedra;

# include "PalletObjectData.hpp"
# include "NewPalletObjectData.hpp"

template<
	typename TypeData
>
struct NewPolyHedra_Type_Object
{
	private:
	NewPolyHedra_Type_PalletObjectData<TypeData> *		PalletObjectData;

	public:
	bool	Is() const
	{
		return (PalletObjectData != nullptr);
	}

	public:
	TypeData &	Data()
	{
		return (PalletObjectData -> Data);
	}
	const TypeData &	Data() const
	{
		return (PalletObjectData -> Data);
	}

	public:
	void	ShowFull() { PalletObjectData -> ShowFull(); }
	void	HideFull() { PalletObjectData -> HideFull(); }
	bool	VisibleFull() const { return PalletObjectData -> VisibleFull(); }

	public:
	void	ShowWire() { PalletObjectData -> ShowWire(); }
	void	HideWire() { PalletObjectData -> HideWire(); }
	bool	VisibleWire() const { return PalletObjectData -> VisibleWire(); }

	public:
	NewPolyHedra_PalletObjectManager * Manager()
	{
		return (PalletObjectData -> Manager);
	}
	const NewPolyHedra_PalletObjectManager * Manager() const
	{
		return (PalletObjectData -> Manager);
	}

	public:
	~NewPolyHedra_Type_Object()
	{
		PalletObjectData -> Remove = true;
		/*if (PalletObjectData != nullptr)
		{
			if (!PalletObjectData -> Remove)
			{
				PalletObjectData -> Remove = true;
			}
			else
			{
				delete PalletObjectData;
			}
		}*/
	}
	NewPolyHedra_Type_Object()
		: PalletObjectData(nullptr)
	{ }
	NewPolyHedra_Type_Object(NewPolyHedra_Pallet * pallet)
		: PalletObjectData(sNewPalletObjectData<TypeData>(pallet))
	{ }
	NewPolyHedra_Type_Object(PolyHedra * polyhedra)
		: PalletObjectData(sNewPalletObjectData<TypeData>(polyhedra))
	{ }

	public:
	NewPolyHedra_Type_Object(const NewPolyHedra_Type_Object & other) = delete;
	NewPolyHedra_Type_Object & operator=(const NewPolyHedra_Type_Object & other) = delete;

	public:
	void	Delete()
	{
		if (PalletObjectData == nullptr) { return; }
		PalletObjectData -> Remove = true;
		PalletObjectData = nullptr;
	}
	void	Create(NewPolyHedra_Pallet * pallet)
	{
		if (PalletObjectData != nullptr) { return; }
		PalletObjectData = sNewPalletObjectData<TypeData>(pallet);
	}
	void	Create(PolyHedra * polyhedra)
	{
		if (PalletObjectData != nullptr) { return; }
		PalletObjectData = sNewPalletObjectData<TypeData>(polyhedra);
	}
};

#endif