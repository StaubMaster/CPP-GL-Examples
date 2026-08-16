#ifndef  MANAGER_HPP
# define MANAGER_HPP

# include "ValueType/Light/Base.hpp"
# include "ValueType/Light/Direction.hpp"
# include "ValueType/Light/Point.hpp"
# include "ValueType/Light/Spot.hpp"

struct LightManager
{
	static const unsigned int	Ambient_Limit = 1;
	static const unsigned int	Solar_Limit = 1;
	static const unsigned int	Point_Limit = 1;
	static const unsigned int	Spot_Limit = 4;

	unsigned int	Ambient_Count;
	unsigned int	Solar_Count;
	unsigned int	Point_Count;
	unsigned int	Spot_Count;

	LightBase		Ambient;
	LightDirection	Solar;
	LightPoint		Point_Array[Point_Limit];
	LightSpot		Spot_Array[Spot_Limit];

	void	Clear();

	LightBase *			TakeAmbient();
	LightDirection *	TakeDirection();
	LightPoint *		TakePoint();
	LightSpot *			TakeSpot();

};

#endif