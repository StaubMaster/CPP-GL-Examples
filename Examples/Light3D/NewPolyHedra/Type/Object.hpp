#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_HPP

struct NewPolyHedra_Pallet;
class PolyHedra;

# include "PalletObjectData.hpp"
# include "NewPalletObjectData.hpp"
# include "../NewPallet.hpp"

// here because it works
// try to remove
# include "ObjectManager.hpp"

template<
	typename TypeData
>
struct NewPolyHedra_Type_Object
{
	NewPolyHedra_Type_PalletObjectData<TypeData> *		PalletObjectData;

	bool	Is() const { return (PalletObjectData != nullptr); }

	TypeData &	Data()
	{
		return PalletObjectData -> Data;
	}
	const TypeData &	Data() const
	{
		return PalletObjectData -> Data;
	}

	void	ShowFull() { PalletObjectData -> DisplayFull = true; }
	void	HideFull() { PalletObjectData -> DisplayFull = false; }
	bool	VisibleFull() const { return PalletObjectData -> DisplayFull; }
	
	void	ShowWire() { PalletObjectData -> DisplayWire = true; }
	void	HideWire() { PalletObjectData -> DisplayWire = false; }
	bool	VisibleWire() const { return PalletObjectData -> DisplayWire; }

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
		: PalletObjectData(sNewPalletObjectData<TypeData>(NewPallet(polyhedra)))
	{ }

	NewPolyHedra_Type_Object(const NewPolyHedra_Type_Object & other) = delete;
	NewPolyHedra_Type_Object & operator=(const NewPolyHedra_Type_Object & other) = delete;

	void	Delete()
	{
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
		PalletObjectData = sNewPalletObjectData<TypeData>(NewPallet(polyhedra));
	}
};

#endif