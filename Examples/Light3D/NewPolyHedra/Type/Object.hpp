#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_HPP

# include "PalletObjectData.hpp"

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;

template<
	typename TypeData
>
struct Type_Object
{
	private:
	Type_PalletObjectData<TypeData> *		PalletObjectData;

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
	PalletObjectManager * Manager()
	{
		return (PalletObjectData -> Manager);
	}
	const PalletObjectManager * Manager() const
	{
		return (PalletObjectData -> Manager);
	}

	public:
	~Type_Object()
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
	Type_Object()
		: PalletObjectData(nullptr)
	{ }
	Type_Object(Pallet * pallet)
		: PalletObjectData(Type_PalletObjectData<TypeData>::Make(pallet))
	{ }
	Type_Object(PolyHedra * polyhedra)
		: PalletObjectData(Type_PalletObjectData<TypeData>::Make(polyhedra))
	{ }

	public:
	Type_Object(const Type_Object & other) = delete;
	Type_Object & operator=(const Type_Object & other) = delete;

	public:
	void	Delete()
	{
		if (PalletObjectData == nullptr) { return; }
		PalletObjectData -> Remove = true;
		PalletObjectData = nullptr;
	}
	void	Create(Pallet * pallet)
	{
		if (PalletObjectData != nullptr) { return; }
		PalletObjectData = Type_PalletObjectData<TypeData>::Make(pallet);
	}
	void	Create(PolyHedra * polyhedra)
	{
		if (PalletObjectData != nullptr) { return; }
		PalletObjectData = Type_PalletObjectData<TypeData>::Make(polyhedra);
	}
};
};

#endif