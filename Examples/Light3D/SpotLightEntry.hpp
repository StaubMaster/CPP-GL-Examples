#ifndef  SPOT_LIGHT_ENTRY_HPP
# define SPOT_LIGHT_ENTRY_HPP

# include "ValueType/Vector/F3.hpp"
# include "ValueType/LightSpot.hpp"
# include "PolyHedra/Object.hpp"

struct SpotLightEntry
{
	VectorF3			Origin;
	VectorF3			Target;
	LightSpot *			Light;
	PolyHedraObject		EntryLight;
	PolyHedraObject		EntryHolder;

	~SpotLightEntry();
	SpotLightEntry();

	void	Look(VectorF3 from, VectorF3 to);
	void	Update();

	void	Toggle();
};

#endif