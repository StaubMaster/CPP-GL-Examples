#ifndef  ANCHOR_2D_HPP
# define ANCHOR_2D_HPP

# include "AnchorAxis.hpp"

struct BoxF2;
struct VectorF2;

struct Anchor2D
{
	AnchorAxis	X;
	AnchorAxis	Y;

	Anchor2D(
		VectorF2 & size,
		BoxF2 & dist,
		VectorF2 & normal_center
	);

	public:
	void	ChangeBox(const BoxF2 & boxO, const BoxF2 & boxI);
	void	Update(const VectorF2 & size);
};

#endif