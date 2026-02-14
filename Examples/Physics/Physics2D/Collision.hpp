#ifndef  PHYSICS_2D_COLLISION_HPP
# define PHYSICS_2D_COLLISION_HPP

# include "Physics2D/Object.hpp"

# include "ValueType/AxisBox1D.hpp"

namespace Physics2D
{
	struct PolyGonProjectionData
	{
		AxisBox1D		Box;
		unsigned int	MinUdx;
		unsigned int	MaxUdx;

		~PolyGonProjectionData();
		PolyGonProjectionData();

		PolyGonProjectionData(const PolyGonProjectionData & other);
		PolyGonProjectionData & operator=(const PolyGonProjectionData & other);

		void Consider(float val, unsigned int idx);

		static PolyGonProjectionData Project(
			const Object & obj,
			Point2D normal
		);
	};

	struct PolyGonContactData
	{
		bool			Valid;
		Point2D			Normal;
		float			Distance;
		unsigned int	Contact0Udx;
		unsigned int	Contact1Udx;

		~PolyGonContactData();
		PolyGonContactData();
		PolyGonContactData(const PolyGonContactData & other);
		PolyGonContactData & operator=(const PolyGonContactData & other);

		bool Compare(const PolyGonContactData & other) const;

		static PolyGonContactData Check(
			const Object & obj0,
			const Object & obj1,
			Point2D normal
		);
		static PolyGonContactData Check(
			const Object & obj0,
			const Object & obj1
		);
	};

	/*void Collide(
		const PolyGon & poly_gon_0, const Trans2D & trans_0, Trans2D vel_0,
		const PolyGon & poly_gon_1, const Trans2D & trans_1, Trans2D vel_1
	);*/
};

#endif