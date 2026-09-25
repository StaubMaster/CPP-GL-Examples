#ifndef  COMPARISON_3D_HPP
# define COMPARISON_3D_HPP

# include "Comparison1D.hpp"

struct Comparison3D
{
	public:
	Comparison1D	X;
	Comparison1D	Y;
	Comparison1D	Z;

	public:
	Comparison3D();
	Comparison3D(Comparison1D x, Comparison1D y, Comparison1D z);
	~Comparison3D();

	Comparison3D(const Comparison3D & other);
	Comparison3D & operator=(const Comparison3D & other);

	public:
	bool operator==(const Comparison3D & other);
};

#endif