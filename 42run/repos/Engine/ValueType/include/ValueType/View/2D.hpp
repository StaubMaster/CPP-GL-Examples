#ifndef  VIEW_2D_HPP
# define VIEW_2D_HPP

# include "ValueType/Trans/2D.hpp"

struct View2D
{
	Trans2D	Trans;
	float	Scale;



	~View2D();
	View2D();

	View2D(const View2D & other);
	View2D & operator=(const View2D & other);

	static View2D Default();

	void Change(Trans2D change, float timeDelta);



	VectorF2 forward(VectorF2 p) const;
	VectorF2 reverse(VectorF2 p) const;
};

#endif