#ifndef  ANCHOR_2D_HPP
# define ANCHOR_2D_HPP

# include "Anchor1D.hpp"

struct BoxF2;

struct Anchor2D
{
	Anchor1D X;
	Anchor1D Y;

	Anchor2D(Anchor1D x, Anchor1D y);

	BoxF2	Calculate(BoxF2 Parent);
	void	Calculate(BoxF2 Parent, BoxF2 box);
};

#endif