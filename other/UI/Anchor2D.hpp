#ifndef  ANCHOR_2D_HPP
# define ANCHOR_2D_HPP

# include "Anchor1D.hpp"

struct AxisBox2D;

struct Anchor2D
{
	Anchor1D X;
	Anchor1D Y;

	Anchor2D(Anchor1D x, Anchor1D y);

	AxisBox2D Calculate(AxisBox2D Parent);
};

#endif