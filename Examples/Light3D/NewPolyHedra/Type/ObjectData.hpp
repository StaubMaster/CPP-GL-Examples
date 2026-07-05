#ifndef  NEW_POLYHEDRA_TYPE_OBJECT_DATA_HPP
# define NEW_POLYHEDRA_TYPE_OBJECT_DATA_HPP

# include "../ObjectData.hpp"

/* PolyHedraObjectData
	Trans3D		Trans;
*/

/* PolyHedraUIObjectData
	Trans3D		Trans;
	float		Scale;
	ColorF4		Color;
*/

template<
	typename TypeData
>
struct NewPolyHedra_Type_ObjectData : public NewPolyHedra_ObjectData
{
	TypeData	Data;
};

#endif