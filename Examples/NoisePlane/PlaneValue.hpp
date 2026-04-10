#ifndef  PLANE_VALUE_HPP
# define PLANE_VALUE_HPP

# include "ValueType/ColorF4.hpp"

struct PlaneValue
{
	bool	Known;
	float	Value;
	// Position ?

	~PlaneValue();
	PlaneValue();
	PlaneValue(const PlaneValue & other);
	PlaneValue & operator=(const PlaneValue & other);

	ColorF4		ToColor() const;
};

#endif