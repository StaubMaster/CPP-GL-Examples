#ifndef  LIGHT_MANAGER_HPP
# define LIGHT_MANAGER_HPP

# include "ValueType/Light/Base.hpp"
# include "ValueType/Light/Direction.hpp"
# include "ValueType/Light/Point.hpp"
# include "ValueType/Light/Spot.hpp"

struct LightBufferData;

struct LightManager
{
	static const unsigned int	Ambient_Limit = 1;
	static const unsigned int	Solar_Limit = 1;
	static const unsigned int	Point_Limit = 1;
	static const unsigned int	Spot_Limit = 4;

	unsigned int	Ambient_Count = 0;
	unsigned int	Solar_Count = 0;
	unsigned int	Point_Count = 0;
	unsigned int	Spot_Count = 0;

	LightBase		Ambient;
	LightDirection	Solar;
	LightPoint		Point_Array[Point_Limit];
	LightSpot		Spot_Array[Spot_Limit];

	void	Clear();

	LightBase *			TakeAmbient();
	LightDirection *	TakeDirection();
	LightPoint *		TakePoint();
	LightSpot *			TakeSpot();

	LightBufferData		ToBufferData() const;
};

#endif