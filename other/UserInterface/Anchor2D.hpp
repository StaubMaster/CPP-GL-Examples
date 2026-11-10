#ifndef  ANCHOR_2D_HPP
# define ANCHOR_2D_HPP

# include "Anchor1D.hpp"

struct BoxF2;
struct VectorF2;

struct Anchor2D
{
	Anchor1D X;
	Anchor1D Y;

	Anchor2D(
		VectorF2 & size,
		BoxF2 & dist,
		BoxF2 & margin,
		BoxF2 & boarder,
		BoxF2 & padding,
		VectorF2 & normal_center
	);

	public:
	void	UpdateO(const BoxF2 & boxO);
	void	UpdateO(const BoxF2 & boxO, const BoxF2 & boxI);

	public:
	BoxF2	ToInnerBox(const BoxF2 & boxO) const;
};

#endif