#ifndef  COLLISION_2D_HPP
# define COLLISION_2D_HPP

# include "PolyGon/PolyGon.hpp"
# include "ValueType/Trans2D.hpp"

# include "ValueType/AxisBox1D.hpp"

namespace Collision2D
{
	struct TransPolyGon
	{
		const ::PolyGon & PolyGon;
		const ::Trans2D & Trans;

		unsigned int Corners() const;
		Point2D TransCorner(unsigned int idx) const;

		~TransPolyGon();
		TransPolyGon() = delete;

		TransPolyGon(const TransPolyGon & other);
		TransPolyGon & operator=(const TransPolyGon & other) = delete;

		TransPolyGon(const ::PolyGon & poly_gon, const ::Trans2D & trans);
		TransPolyGon(const ::PolyGon * poly_gon, const ::Trans2D & trans);
	};

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
			const TransPolyGon & poly_gon,
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
			const TransPolyGon & poly_gon_0,
			const TransPolyGon & poly_gon_1,
			Point2D normal
		);
		static PolyGonContactData Check(
			const TransPolyGon & poly_gon_0,
			const TransPolyGon & poly_gon_1
		);
	};

	/*void Collide(
		const PolyGon & poly_gon_0, const Trans2D & trans_0, Trans2D vel_0,
		const PolyGon & poly_gon_1, const Trans2D & trans_1, Trans2D vel_1
	);*/
};

#endif