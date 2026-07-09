#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_MANAGER_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_MANAGER_HPP

# include "../ObjectManager.hpp"
# include "PalletObjectData.hpp"
# include "PalletObjectManager.hpp"

namespace NewPolyHedra
{
template<typename TypeData>
struct Type_Data_ObjectManager : public ObjectManager
{
	public:
	static Type_Data_ObjectManager *	Current;

	public:
	~Type_Data_ObjectManager()
	{
		Current = nullptr;
	}
	Type_Data_ObjectManager()
	{
		Current = this;
	}
	Type_Data_ObjectManager(const Type_Data_ObjectManager & other) = delete;
	Type_Data_ObjectManager & operator=(const Type_Data_ObjectManager & other) = delete;
};

template<typename TypeData> Type_Data_ObjectManager<TypeData> * Type_Data_ObjectManager<TypeData>::Current = nullptr;



template<typename TypeData, typename TypeInstanceData>
struct Type_ObjectManager : public Type_Data_ObjectManager<TypeData>
{
	public:
	~Type_ObjectManager() = default;
	Type_ObjectManager() = default;
	Type_ObjectManager(const Type_ObjectManager & other) = delete;
	Type_ObjectManager & operator=(const Type_ObjectManager & other) = delete;

	public:
	PalletObjectManager *	NewPalletObjectManager() override
	{
		return new Type_PalletObjectManager<TypeData, TypeInstanceData>();
	}
	PalletObjectData *	NewPalletObjectData() override
	{
		return new Type_PalletObjectData<TypeData>();
	}
};
};

#endif