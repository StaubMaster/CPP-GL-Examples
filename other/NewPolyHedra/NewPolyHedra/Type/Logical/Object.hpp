#ifndef  NEW_POLYHEDRA_TYPE_LOGICAL_OBJECT_HPP
# define NEW_POLYHEDRA_TYPE_LOGICAL_OBJECT_HPP

# include "NewPolyHedra/Base/Logical/Object.hpp"
# include "NewPolyHedra/Type/Display/Object.hpp"

class PolyHedra;

namespace NewPolyHedra
{
struct Pallet;

template<typename LogicalData> struct TypeLogicalObject : public BaseLogicalObject
{
	public:
	DataDisplayObject<LogicalData> *	DisplayObject = nullptr;

	public:
	~TypeLogicalObject() = default;
	TypeLogicalObject() = default;
	TypeLogicalObject(const TypeLogicalObject & other) = delete;
	TypeLogicalObject & operator=(const TypeLogicalObject & other) = delete;

	public:
	LogicalData		Data;

	public:
	void	InstancePut() const override;
};
};

#endif